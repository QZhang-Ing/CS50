import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/index")
@login_required
def index():
    # get info from db
    rows = db.execute("SELECT * FROM transfer WHERE userid = :userid", userid=session["user_id"])
    deposit = db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])[0]["cash"]

    # list pass to index.html
    grandtotal = deposit
    holdings = []
    for index, row in enumerate(rows):
        holdings_price = lookup(row['symbol'])
        # append the list of holdings
        holdings.append(list((holdings_price['symbol'], holdings_price['name'], int(row['shares']), holdings_price['price'], holdings_price['price'] * int(row['shares']))))
        grandtotal = grandtotal + holdings[index][4]

    return render_template("index.html", holdings=holdings, deposit=deposit, grandtotal=grandtotal)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Valid Sympol needed!")
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Invalid share number detected!")
        price=lookup(symbol)
        if not price:
            return apology("Undefined Sympol/Stock Symbol!")
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        deposit = rows[0]["cash"]
        if price["price"] * shares > deposit:
            return apology("Insurfficient balance")
        else:
            # get current datetime
            now = datetime.now()
            # transfer it to  dd/mm/yy H:M:S
            now_string = now.strftime("%d/%m/%Y %H:%M:%S")

            # write each buying in the table
            db.execute("INSERT INTO transfer (userid, username, status, symbol, shares, price, time) VALUES (:userid, :name, :status, :symbol, :shares, :price, :time)", userid=session["user_id"], name=rows[0]["username"], status="buy in", symbol=symbol, shares=shares, price=price["price"], time=now_string)
            stock = db.execute("SELECT shares FROM holdings WHERE userid = :userid AND symbol = :symbol", userid = session["user_id"], symbol = symbol)
            # if not already exists:
            if not stock:
                db.execute("INSERT INTO holdings (userid, symbol, shares, price) VALUES (:userid, :symbol, :shares, :price)", userid = session["user_id"], symbol = symbol, shares = shares, price=price["price"])
            else:
                new_shares = stock[0]["shares"] + shares
                db.execute("UPDATE holdings SET shares = :shares WHERE userid = :userid AND symbol = :symbol", userid = session["user_id"], symbol = symbol, shares = shares)

            # update the current deposit of users
            new_deposit = deposit - shares * price["price"]
            db.execute("UPDATE users SET cash = ? WHERE id = ?", (new_deposit, session["user_id"]))
            return redirect("/index")

@app.route("/history")
@login_required
def history():
    # query database with the transactions history
    rows = db.execute("SELECT * FROM transfer WHERE userid = :userid",
                            userid=session["user_id"])

    historys = []
    for row in rows:
        historys.append(list((row['symbol'], row['status'], row['shares'], row['price'], row['time'])))

    return render_template("history.html", historys=historys)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/index")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/index")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        price=lookup(symbol)
        if not price:
            return apology("Undefined Sympol/Stock Symbol!")
        return render_template("quoted.html", price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("name")
        userid = db.execute("SELECT id FROM users WHERE username = :name",name=name)
        if not name or userid:
            return apology("must provide username", 403)
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not password or not confirmation or password != confirmation:
            return apology("must provide volid password", 403)
        hashpass = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES (:name, :hashpass)", name=name, hashpass=hashpass)
        return redirect("/index")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        return render_template("sell.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Valid Sympol needed!")

        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Invalid share number detected!")
        price=lookup(symbol)
        if not price:
            return apology("Undefined Sympol/Stock Symbol!")

        # get possessed shares amount of the stock user want to sell
        possessed_shares = db.execute("SELECT shares FROM holdings WHERE userid = :userid AND symbol = :symbol", userid = session["user_id"], symbol = symbol)[0]['shares']
        # if user want to sell more shares than he or she possessed
        new_shares = possessed_shares - shares
        if new_shares < 0:
            return apology("Unsufficient shares to sell!")
        elif new_shares == 0:
            db.execute("DELETE FROM holdings WHERE userid = :userid AND symbol = :symbol", symbol=symbol, userid=session["user_id"])
        else:
            db.execute("UPDATE holdings SET shares = :shares WHERE userid = :userid AND symbol = :symbol", shares = new_shares,symbol=symbol, userid=session["user_id"])
        # update the current deposit of users
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        deposit = rows[0]["cash"]
        new_deposit = deposit + shares * price["price"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (new_deposit, session["user_id"]))
        # update history
        # get current datetime
        now = datetime.now()
        # transfer it to  dd/mm/yy H:M:S
        now_string = now.strftime("%d/%m/%Y %H:%M:%S")
        db.execute("INSERT INTO transfer (userid, username, status, symbol, shares, price, time) VALUES (:userid, :name, :status, :symbol, :shares, :price, :time)", userid=session["user_id"], name=rows[0]["username"], status="sell out", symbol=symbol, shares=shares, price=price["price"], time=now_string)

        return redirect("/index")



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

SELECT COUNT(title) FROM movies
JOIN rating on movies.id = ratings.movie_id
WHERE rating = 10
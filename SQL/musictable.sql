USE BrandMedia;

CREATE TABLE music(
		song_id INT PRIMARY KEY,
        artist_name VARCHAR(16),
        track_name VARCHAR(16),
        album_title VARCHAR(16),
        release_date DATE,
        songwriters VARCHAR(64),
        producers VARCHAR(64),
        contributing_artist VARCHAR(64)
);

DESCRIBE music;

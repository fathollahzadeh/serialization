package at.tugraz.objects.imdb;

public class MoviesDirectors {
	private Directors directors;
	private Integer movieId;

	public MoviesDirectors(Directors directors, Integer movieId) {
		this.directors = directors;
		this.movieId = movieId;
	}

	public Directors getDirectors() {
		return directors;
	}

	public void setDirectors(Directors directors) {
		this.directors = directors;
	}

	public Integer getMovieId() {
		return movieId;
	}

	public void setMovieId(Integer movieId) {
		this.movieId = movieId;
	}
}

package at.tugraz.datamodel.imdb;

public class MoviesGenres {

	private Integer moviesId;
	private String genre;

	public MoviesGenres(Integer moviesId, String genre) {
		this.moviesId = moviesId;
		this.genre = genre;
	}

	public Integer getMoviesId() {
		return moviesId;
	}

	public void setMoviesId(Integer moviesId) {
		this.moviesId = moviesId;
	}

	public String getGenre() {
		return genre;
	}

	public void setGenre(String genre) {
		this.genre = genre;
	}
}

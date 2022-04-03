package at.tugraz.datamodel.imdb;

public class DirectorsGenres {

	private Integer directorId;
	private String genre;
	private Float prob;

	public DirectorsGenres(Integer directorId, String genre, Float prob) {
		this.directorId = directorId;
		this.genre = genre;
		this.prob = prob;
	}

	public Integer getDirectorId() {
		return directorId;
	}

	public void setDirectorId(Integer directorId) {
		this.directorId = directorId;
	}

	public String getGenre() {
		return genre;
	}

	public void setGenre(String genre) {
		this.genre = genre;
	}

	public Float getProb() {
		return prob;
	}

	public void setProb(Float prob) {
		this.prob = prob;
	}
}

package at.tugraz.datamodel.imdb;

public class Roles {
	private Actors actor;
	private Integer movieId;
	private String role;

	public Roles(Actors actor, Integer movieId, String role) {
		this.actor = actor;
		this.movieId = movieId;
		this.role = role;
	}

	public Actors getActor() {
		return actor;
	}

	public void setActor(Actors actor) {
		this.actor = actor;
	}

	public Integer getMovieId() {
		return movieId;
	}

	public void setMovieId(Integer movieId) {
		this.movieId = movieId;
	}

	public String getRole() {
		return role;
	}

	public void setRole(String role) {
		this.role = role;
	}
}

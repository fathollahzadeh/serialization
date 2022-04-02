package at.tugraz.objects.imdb;

public class Roles {
	private Actors actor;
	private Integer movieId;
	private String role;

	public Roles(Actors actor, Integer movieId, String role) {
		this.actor = actor;
		this.movieId = movieId;
		this.role = role;
	}
}

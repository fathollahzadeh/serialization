package at.tugraz.objects.imdb;

import java.util.List;

public class Directors {
	private Integer id;
	private String firstName;
	private String lastName;
	private List<DirectorsGenres> directorsGenres;

	public Directors(Integer id, String firstName, String lastName, List<DirectorsGenres> directorsGenres) {
		this.id = id;
		this.firstName = firstName;
		this.lastName = lastName;
		this.directorsGenres = directorsGenres;
	}

	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public String getFirstName() {
		return firstName;
	}

	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public String getLastName() {
		return lastName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public List<DirectorsGenres> getDirectorsGenres() {
		return directorsGenres;
	}

	public void setDirectorsGenres(List<DirectorsGenres> directorsGenres) {
		this.directorsGenres = directorsGenres;
	}
}

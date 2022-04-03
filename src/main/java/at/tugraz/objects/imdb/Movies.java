package at.tugraz.objects.imdb;

import at.tugraz.util.RootObject;

import java.util.List;

public class Movies extends RootObject {

	private Integer id;
	private String name;
	private Integer year;
	private Float rank;
	private List<MoviesGenres> genres;
	private List<Roles> roles;
	private List<MoviesDirectors> directors;

	public Movies(Integer id, String name, Integer year, Float rank, List<MoviesGenres> genres, List<Roles> roles, List<MoviesDirectors> directors) {
		this.id = id;
		this.name = name;
		this.year = year;
		this.rank = rank;
		this.genres = genres;
		this.roles = roles;
		this.directors = directors;
	}

	public Integer getId() {
		return id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Integer getYear() {
		return year;
	}

	public void setYear(Integer year) {
		this.year = year;
	}

	public Float getRank() {
		return rank;
	}

	public void setRank(Float rank) {
		this.rank = rank;
	}

	public List<MoviesGenres> getGenres() {
		return genres;
	}

	public void setGenres(List<MoviesGenres> genres) {
		this.genres = genres;
	}

	public List<Roles> getRoles() {
		return roles;
	}

	public void setRoles(List<Roles> roles) {
		this.roles = roles;
	}

	public List<MoviesDirectors> getDirectors() {
		return directors;
	}

	public void setDirectors(List<MoviesDirectors> directors) {
		this.directors = directors;
	}
}

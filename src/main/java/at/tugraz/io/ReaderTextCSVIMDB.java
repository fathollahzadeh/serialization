package at.tugraz.io;

import at.tugraz.datamodel.imdb.Actors;
import at.tugraz.datamodel.imdb.Directors;
import at.tugraz.datamodel.imdb.DirectorsGenres;
import at.tugraz.datamodel.imdb.Movies;
import at.tugraz.datamodel.imdb.MoviesDirectors;
import at.tugraz.datamodel.imdb.MoviesGenres;
import at.tugraz.datamodel.imdb.Roles;
import at.tugraz.util.RootObject;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.HashMap;

public class ReaderTextCSVIMDB extends ReaderText {

	private String actorsPath;
	private String directorsGenresPath;
	private String directorsPath;
	private String moviesGenresPath;
	private String rolesPath;
	private String moviesDirectorsPath;
	private String moviesPath;


	HashMap<Integer, Actors> actorsMap = new HashMap<Integer, Actors>();
	HashMap<Integer, ArrayList<DirectorsGenres>> directorsGenresMap = new HashMap<Integer, ArrayList<DirectorsGenres>>();
	HashMap<Integer, Directors> directorsMap = new HashMap<Integer, Directors>();
	HashMap<Integer, ArrayList<Roles>> rolesMap = new HashMap<Integer, ArrayList<Roles>>();
	HashMap<Integer, ArrayList<MoviesDirectors>> moviesDirectorsMap = new HashMap<Integer, ArrayList<MoviesDirectors>>();
	HashMap<Integer, ArrayList<MoviesGenres>> moviesGenresMap = new HashMap<Integer, ArrayList<MoviesGenres>>();

	public ReaderTextCSVIMDB(String fileName) {
		super(fileName);
	}

	@Override public ArrayList<RootObject> getObjects() {
		this.actorsPath = fileName + "/actors.csv";
		this.directorsGenresPath = fileName + "/directors_genres.csv";
		this.directorsPath = fileName + "/directors.csv";
		this.moviesGenresPath = fileName + "/movies_genres.csv";
		this.rolesPath = fileName + "/roles.csv";
		this.moviesDirectorsPath = fileName + "/movies_directors.csv";
		this.moviesPath = fileName + "/movies.csv";

		loadMoviesGenresData();
		loadActorsData();
		loadDirectorsGenresData();
		loadDirectorsData();
		loadRolesData();
		loadMoviesDirectorsData();

		try(BufferedReader br = new BufferedReader(new FileReader(moviesPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Integer movieId = Integer.parseInt(data[0]);

				ArrayList<MoviesGenres> moviesGenres;
				if(moviesGenresMap.containsKey(movieId))
					moviesGenres = moviesGenresMap.get(movieId);
				else
					moviesGenres = new ArrayList<>();

				ArrayList<Roles> roles;
				if(rolesMap.containsKey(movieId))
					roles = rolesMap.get(movieId);
				else
					roles = new ArrayList<>();

				ArrayList<MoviesDirectors> moviesDirectors;
				if(moviesDirectorsMap.containsKey(movieId))
					moviesDirectors = moviesDirectorsMap.get(movieId);
				else
					moviesDirectors = new ArrayList<>();

				Float rank = data[3] != null && !data[3].equals("") ? Float.parseFloat(data[3]) : null;
				Movies movie = new Movies(movieId, data[1], Integer.parseInt(data[2]), rank, moviesGenres, roles,
					moviesDirectors);

				objects.add(movie);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}

		return objects;
	}
	// Load Movies Genres Data
	private void loadMoviesGenresData() {
		try(BufferedReader br = new BufferedReader(new FileReader(moviesGenresPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Integer moviesId = Integer.parseInt(data[0]);
				MoviesGenres movieGenre = new MoviesGenres(moviesId, data[1]);
				ArrayList<MoviesGenres> values;
				if(moviesGenresMap.containsKey(moviesId))
					values = moviesGenresMap.get(moviesId);
				else
					values = new ArrayList<>();
				values.add(movieGenre);
				moviesGenresMap.put(moviesId, values);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Actors Data
	private void loadActorsData() {
		try(BufferedReader br = new BufferedReader(new FileReader(actorsPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Actors actor = new Actors(Integer.parseInt(data[0]), data[1], data[2], data[3].charAt(0));
				actorsMap.put(actor.getId(), actor);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Directors Genres Data
	private void loadDirectorsGenresData() {
		try(BufferedReader br = new BufferedReader(new FileReader(directorsGenresPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Integer directorId = Integer.parseInt(data[0]);
				DirectorsGenres directorGenre = new DirectorsGenres(directorId, data[1], Float.parseFloat(data[2]));
				ArrayList<DirectorsGenres> values;
				if(directorsGenresMap.containsKey(directorId))
					values = directorsGenresMap.get(directorId);
				else
					values = new ArrayList<DirectorsGenres>();
				values.add(directorGenre);
				directorsGenresMap.put(directorId, values);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Directors Data
	private void loadDirectorsData() {
		try(BufferedReader br = new BufferedReader(new FileReader(directorsPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Integer directorId = Integer.parseInt(data[0]);
				ArrayList<DirectorsGenres> values;
				if(directorsGenresMap.containsKey(directorId))
					values = directorsGenresMap.get(directorId);
				else
					values = new ArrayList<>();
				Directors director = new Directors(directorId, data[1], data[2], values);
				directorsMap.put(directorId, director);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Roles Data
	private void loadRolesData() {
		try(BufferedReader br = new BufferedReader(new FileReader(rolesPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Integer actorId = Integer.parseInt(data[0]);
				Integer movieId = Integer.parseInt(data[1]);
				Actors actor = actorsMap.get(actorId);
				Roles role = new Roles(actor, movieId, data[2]);
				ArrayList<Roles> values;
				if(rolesMap.containsKey(movieId))
					values = rolesMap.get(movieId);
				else
					values = new ArrayList<>();
				values.add(role);
				rolesMap.put(movieId, values);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	// Load Movies Directors Data
	private void loadMoviesDirectorsData() {
		try(BufferedReader br = new BufferedReader(new FileReader(moviesDirectorsPath))) {
			String line;
			// skip first row:
			br.readLine();
			while((line = br.readLine()) != null) {
				String[] data = getData(line);
				Integer directorId = Integer.parseInt(data[0]);
				Integer movieId = Integer.parseInt(data[1]);
				Directors director = directorsMap.get(directorId);
				MoviesDirectors movieDirector = new MoviesDirectors(director, movieId);
				ArrayList<MoviesDirectors> values;
				if(moviesDirectorsMap.containsKey(movieId))
					values = moviesDirectorsMap.get(movieId);
				else
					values = new ArrayList<>();
				values.add(movieDirector);
				moviesDirectorsMap.put(movieId, values);
			}
		}
		catch(Exception e) {
			throw new RuntimeException(e);
		}
	}

	private String[] getData(String line) {
		String[] data = line.split("\t", -1);
		return data;
	}
}

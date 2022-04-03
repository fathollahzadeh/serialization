package at.tugraz.datamodel.twitter;

import java.util.ArrayList;
import java.util.List;

import at.tugraz.util.RootObject;

public class Entities extends RootObject {

	private List<HashtagEntity> hashtags;
	private List<MediaEntity> media;
	private List<URLEntity> urls;
	private List<UserMentionEntity> user_mentions;
	private List<SymbolEntity> symbols;
	private List<PollEntity> polls;

	public Entities() {
		this.hashtags = new ArrayList<>();
		this.media = new ArrayList<>();
		this.urls = new ArrayList<>();
		this.user_mentions = new ArrayList<>();
		this.symbols = new ArrayList<>();
		this.polls = new ArrayList<>();
	}

	public List<HashtagEntity> getHashtags() {
		return hashtags;
	}

	public void setHashtags(List<HashtagEntity> hashtags) {
		this.hashtags = hashtags;
	}

	public List<MediaEntity> getMedia() {
		return media;
	}

	public void setMedia(List<MediaEntity> media) {
		this.media = media;
	}

	public List<URLEntity> getUrls() {
		return urls;
	}

	public void setUrls(List<URLEntity> urls) {
		this.urls = urls;
	}

	public List<UserMentionEntity> getUser_mentions() {
		return user_mentions;
	}

	public void setUser_mentions(List<UserMentionEntity> user_mentions) {
		this.user_mentions = user_mentions;
	}

	public List<SymbolEntity> getSymbols() {
		return symbols;
	}

	public void setSymbols(List<SymbolEntity> symbols) {
		this.symbols = symbols;
	}

	public List<PollEntity> getPolls() {
		return polls;
	}

	public void setPolls(List<PollEntity> polls) {
		this.polls = polls;
	}
}

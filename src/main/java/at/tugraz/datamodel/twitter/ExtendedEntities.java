package at.tugraz.datamodel.twitter;

import java.util.List;

import at.tugraz.util.RootObject;

public class ExtendedEntities extends RootObject {

	private List<MediaEntity> media;

	public List<MediaEntity> getMedia() {
		return media;
	}

	public void setMedia(List<MediaEntity> media) {
		this.media = media;
	}
}

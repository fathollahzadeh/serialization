package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

public class MediaSizesEntity extends RootObject {

	private SizeEntity thumb;
	private SizeEntity large;
	private SizeEntity medium;
	private SizeEntity small;

	public SizeEntity getThumb() {
		return thumb;
	}

	public void setThumb(SizeEntity thumb) {
		this.thumb = thumb;
	}

	public SizeEntity getLarge() {
		return large;
	}

	public void setLarge(SizeEntity large) {
		this.large = large;
	}

	public SizeEntity getMedium() {
		return medium;
	}

	public void setMedium(SizeEntity medium) {
		this.medium = medium;
	}

	public SizeEntity getSmall() {
		return small;
	}

	public void setSmall(SizeEntity small) {
		this.small = small;
	}
}


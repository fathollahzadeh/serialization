package at.tugraz.datamodel.twitter;

import at.tugraz.util.RootObject;

import java.util.ArrayList;
import java.util.List;

public class VideoEntity extends RootObject {

	private List<Integer> aspect_ratio;
	private int duration_millis;
	private List<VariantEntity> variants;

	public VideoEntity() {
		this.aspect_ratio = new ArrayList<>();
		this.variants = new ArrayList<>();
	}

	public List<Integer> getAspect_ratio() {
		return aspect_ratio;
	}

	public void setAspect_ratio(List<Integer> aspect_ratio) {
		this.aspect_ratio = aspect_ratio;
	}

	public int getDuration_millis() {
		return duration_millis;
	}

	public void setDuration_millis(int duration_millis) {
		this.duration_millis = duration_millis;
	}

	public List<VariantEntity> getVariants() {
		return variants;
	}

	public void setVariants(List<VariantEntity> variants) {
		this.variants = variants;
	}
}

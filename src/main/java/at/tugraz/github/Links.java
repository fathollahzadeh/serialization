package at.tugraz.github;

import at.tugraz.util.Base;
import at.tugraz.util.RootData;

import java.util.List;

public class Links extends Base implements RootData {
    private Link self;
    private Link html;
    private Link issue;
    private Link comments;
    private Link reviewComments;
    private Link reviewComment;
    private Link commits;
    private Link statuses;

    @Override
    public List<RootData> generateObjects(int number) {
        return null;
    }

    @Override
    public RootData javaDefaultDeserialization(byte[] buf) {
        return null;
    }

    @Override
    public byte[] jsonSerialization() {
        return new byte[0];
    }

    @Override
    public RootData jsonDeserialization(byte[] buf) {
        return null;
    }

    @Override
    public byte[] jsonSerialization_withGZIP() {
        return new byte[0];
    }

    @Override
    public RootData jsonDeserialization_withGZIP(byte[] buf) {
        return null;
    }

    @Override
    public byte[] protocolBufferWrite() {
        return new byte[0];
    }

    @Override
    public RootData protocolBufferRead(byte[] buf) {
        return null;
    }

    @Override
    public byte[] writeByteBuffer() {
        return new byte[0];
    }

    @Override
    public RootData readByteBuffer(byte[] buffData) {
        return null;
    }

    @Override
    public byte[] bsonSerialization() {
        return new byte[0];
    }

    @Override
    public RootData bsonDeSerialization(byte[] buffData) {
        return null;
    }

    @Override
    public int compareTo(RootData rootData) {
        return 0;
    }

    public Link getSelf() {
        return self;
    }

    public void setSelf(Link self) {
        this.self = self;
    }

    public Link getHtml() {
        return html;
    }

    public void setHtml(Link html) {
        this.html = html;
    }

    public Link getIssue() {
        return issue;
    }

    public void setIssue(Link issue) {
        this.issue = issue;
    }

    public Link getComments() {
        return comments;
    }

    public void setComments(Link comments) {
        this.comments = comments;
    }

    public Link getReviewComments() {
        return reviewComments;
    }

    public void setReviewComments(Link reviewComments) {
        this.reviewComments = reviewComments;
    }

    public Link getReviewComment() {
        return reviewComment;
    }

    public void setReviewComment(Link reviewComment) {
        this.reviewComment = reviewComment;
    }

    public Link getCommits() {
        return commits;
    }

    public void setCommits(Link commits) {
        this.commits = commits;
    }

    public Link getStatuses() {
        return statuses;
    }

    public void setStatuses(Link statuses) {
        this.statuses = statuses;
    }
}

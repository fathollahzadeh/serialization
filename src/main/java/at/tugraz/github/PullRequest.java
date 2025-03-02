package at.tugraz.github;
import at.tugraz.util.Base;
import at.tugraz.util.RootData;

import java.util.List;

public class PullRequest extends Base implements RootData {
    private String url;
    private int id;
    private String nodeId;
    private String htmlUrl;
    private String diffUrl;
    private String patchUrl;
    private String issueUrl;
    private int number;
    private String state;
    private boolean locked;
    private String title;
    private User user;
    private String body;
    private String createdAt;
    private String updatedAt;
    private String closedAt;
    private String mergedAt;
    private String mergeCommitSha;
    private User assignee;
    private List<User> assignees;
    private List<RequestedReviewer> requestedReviewers;
    private List<Object> requestedTeams;
    private List<Object> labels;
    private Object milestone;
    private boolean draft;
    private String commitsUrl;
    private String reviewCommentsUrl;
    private String reviewCommentUrl;
    private String commentsUrl;
    private String statusesUrl;
    private Head head;
    private BasePR base;
    private Links links;
    private String authorAssociation;
    private Object autoMerge;
    private Object activeLockReason;
    private boolean merged;
    private Object mergeable;
    private Object rebaseable;
    private String mergeableState;
    private User mergedBy;
    private int comments;
    private int reviewComments;
    private boolean maintainerCanModify;
    private int commits;
    private int additions;
    private int deletions;
    private int changedFiles;

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

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getNodeId() {
        return nodeId;
    }

    public void setNodeId(String nodeId) {
        this.nodeId = nodeId;
    }

    public String getHtmlUrl() {
        return htmlUrl;
    }

    public void setHtmlUrl(String htmlUrl) {
        this.htmlUrl = htmlUrl;
    }

    public String getDiffUrl() {
        return diffUrl;
    }

    public void setDiffUrl(String diffUrl) {
        this.diffUrl = diffUrl;
    }

    public String getPatchUrl() {
        return patchUrl;
    }

    public void setPatchUrl(String patchUrl) {
        this.patchUrl = patchUrl;
    }

    public String getIssueUrl() {
        return issueUrl;
    }

    public void setIssueUrl(String issueUrl) {
        this.issueUrl = issueUrl;
    }

    public int getNumber() {
        return number;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public boolean isLocked() {
        return locked;
    }

    public void setLocked(boolean locked) {
        this.locked = locked;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }

    public String getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(String createdAt) {
        this.createdAt = createdAt;
    }

    public String getUpdatedAt() {
        return updatedAt;
    }

    public void setUpdatedAt(String updatedAt) {
        this.updatedAt = updatedAt;
    }

    public String getClosedAt() {
        return closedAt;
    }

    public void setClosedAt(String closedAt) {
        this.closedAt = closedAt;
    }

    public String getMergedAt() {
        return mergedAt;
    }

    public void setMergedAt(String mergedAt) {
        this.mergedAt = mergedAt;
    }

    public String getMergeCommitSha() {
        return mergeCommitSha;
    }

    public void setMergeCommitSha(String mergeCommitSha) {
        this.mergeCommitSha = mergeCommitSha;
    }

    public User getAssignee() {
        return assignee;
    }

    public void setAssignee(User assignee) {
        this.assignee = assignee;
    }

    public List<User> getAssignees() {
        return assignees;
    }

    public void setAssignees(List<User> assignees) {
        this.assignees = assignees;
    }

    public List<RequestedReviewer> getRequestedReviewers() {
        return requestedReviewers;
    }

    public void setRequestedReviewers(List<RequestedReviewer> requestedReviewers) {
        this.requestedReviewers = requestedReviewers;
    }

    public List<Object> getRequestedTeams() {
        return requestedTeams;
    }

    public void setRequestedTeams(List<Object> requestedTeams) {
        this.requestedTeams = requestedTeams;
    }

    public List<Object> getLabels() {
        return labels;
    }

    public void setLabels(List<Object> labels) {
        this.labels = labels;
    }

    public Object getMilestone() {
        return milestone;
    }

    public void setMilestone(Object milestone) {
        this.milestone = milestone;
    }

    public boolean isDraft() {
        return draft;
    }

    public void setDraft(boolean draft) {
        this.draft = draft;
    }

    public String getCommitsUrl() {
        return commitsUrl;
    }

    public void setCommitsUrl(String commitsUrl) {
        this.commitsUrl = commitsUrl;
    }

    public String getReviewCommentsUrl() {
        return reviewCommentsUrl;
    }

    public void setReviewCommentsUrl(String reviewCommentsUrl) {
        this.reviewCommentsUrl = reviewCommentsUrl;
    }

    public String getReviewCommentUrl() {
        return reviewCommentUrl;
    }

    public void setReviewCommentUrl(String reviewCommentUrl) {
        this.reviewCommentUrl = reviewCommentUrl;
    }

    public String getCommentsUrl() {
        return commentsUrl;
    }

    public void setCommentsUrl(String commentsUrl) {
        this.commentsUrl = commentsUrl;
    }

    public String getStatusesUrl() {
        return statusesUrl;
    }

    public void setStatusesUrl(String statusesUrl) {
        this.statusesUrl = statusesUrl;
    }

    public Head getHead() {
        return head;
    }

    public void setHead(Head head) {
        this.head = head;
    }

    public BasePR getBase() {
        return base;
    }

    public void setBase(BasePR base) {
        this.base = base;
    }

    public Links getLinks() {
        return links;
    }

    public void setLinks(Links links) {
        this.links = links;
    }

    public String getAuthorAssociation() {
        return authorAssociation;
    }

    public void setAuthorAssociation(String authorAssociation) {
        this.authorAssociation = authorAssociation;
    }

    public Object getAutoMerge() {
        return autoMerge;
    }

    public void setAutoMerge(Object autoMerge) {
        this.autoMerge = autoMerge;
    }

    public Object getActiveLockReason() {
        return activeLockReason;
    }

    public void setActiveLockReason(Object activeLockReason) {
        this.activeLockReason = activeLockReason;
    }

    public boolean isMerged() {
        return merged;
    }

    public void setMerged(boolean merged) {
        this.merged = merged;
    }

    public Object getMergeable() {
        return mergeable;
    }

    public void setMergeable(Object mergeable) {
        this.mergeable = mergeable;
    }

    public Object getRebaseable() {
        return rebaseable;
    }

    public void setRebaseable(Object rebaseable) {
        this.rebaseable = rebaseable;
    }

    public String getMergeableState() {
        return mergeableState;
    }

    public void setMergeableState(String mergeableState) {
        this.mergeableState = mergeableState;
    }

    public User getMergedBy() {
        return mergedBy;
    }

    public void setMergedBy(User mergedBy) {
        this.mergedBy = mergedBy;
    }

    public int getComments() {
        return comments;
    }

    public void setComments(int comments) {
        this.comments = comments;
    }

    public int getReviewComments() {
        return reviewComments;
    }

    public void setReviewComments(int reviewComments) {
        this.reviewComments = reviewComments;
    }

    public boolean isMaintainerCanModify() {
        return maintainerCanModify;
    }

    public void setMaintainerCanModify(boolean maintainerCanModify) {
        this.maintainerCanModify = maintainerCanModify;
    }

    public int getCommits() {
        return commits;
    }

    public void setCommits(int commits) {
        this.commits = commits;
    }

    public int getAdditions() {
        return additions;
    }

    public void setAdditions(int additions) {
        this.additions = additions;
    }

    public int getDeletions() {
        return deletions;
    }

    public void setDeletions(int deletions) {
        this.deletions = deletions;
    }

    public int getChangedFiles() {
        return changedFiles;
    }

    public void setChangedFiles(int changedFiles) {
        this.changedFiles = changedFiles;
    }
}

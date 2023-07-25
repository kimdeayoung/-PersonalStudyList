package academy.pocu.comp2500.assignment1;

import java.time.OffsetDateTime;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;

public class Post {
    private final String userId;
    private final String authorName;

    private String title;
    private String body;

    private final OffsetDateTime createdDateTime;
    private OffsetDateTime modifiedDateTime;

    private HashSet<String> tags;
    private ArrayList<Comment> comments;

    private Map<ReactionType, HashSet<String>> reactions;

    public Post(String userId, String authorName, String title, String body) {
        this.userId = userId;
        this.authorName = authorName;
        this.title = title;
        this.body = body;
        OffsetDateTime dateTimeNow = OffsetDateTime.now();
        this.createdDateTime = dateTimeNow;
        this.modifiedDateTime = dateTimeNow;
        this.tags = new HashSet<>();
        this.comments = new ArrayList<>();
        this.reactions = new HashMap<>();
    }

    public String getUserId() {
        return this.userId;
    }

    public String getAuthorName() {
        return this.authorName;
    }

    public String getTitle() {
        return this.title;
    }

    public String getBody() {
        return this.body;
    }

    public OffsetDateTime getCreatedDateTime() {
        return this.createdDateTime;
    }

    public OffsetDateTime getModifiedDateTime() {
        return this.modifiedDateTime;
    }

    public ArrayList<Comment> getComments() {
        ArrayList<Comment> comments = new ArrayList<>();
        for (Comment comment : this.comments) {
            comments.add(comment);
        }

        comments.sort((arg1, arg2) -> -Integer.compare(arg1.getCommentPriority(), arg2.getCommentPriority()));

        return comments;
    }

    public HashSet<String> getTags() {
        return this.tags;
    }

    public boolean hasTag(String tag) {
        return this.tags.contains(tag);
    }

    public void addTag(String authorId, String tag) {
        this.tags.add(tag);
    }

    public boolean editTitle(String userId, String title) {
        if (this.userId.equals(userId)) {
            this.title = title;
            this.modifiedDateTime = OffsetDateTime.now();
            return true;
        }
        return false;
    }

    public boolean editBody(String userId, String body) {
        if (this.userId.equals(userId)) {
            this.body = body;
            this.modifiedDateTime = OffsetDateTime.now();
            return true;
        }
        return false;
    }

    public void addComment(Comment comment) {
        this.comments.add(comment);
    }

    public void addReaction(String userId, ReactionType reactionType) {
        if (getAddedReactionType(userId) == null) {
            HashSet<String> userIds = this.reactions.getOrDefault(reactionType, null);
            if (userIds == null) {
                userIds = new HashSet<>();
                this.reactions.put(reactionType, userIds);
            }
            userIds.add(userId);
        }
    }

    public boolean removeReaction(String userId, ReactionType reactionType) {
        HashSet<String> userIds = this.reactions.getOrDefault(reactionType, null);
        if (userIds != null) {
            boolean isSuccess = userIds.remove(userId);
            if (isSuccess) {
                return true;
            }
        }

        return false;
    }

    private ReactionType getAddedReactionType(String userId) {
        for (ReactionType reactionType : this.reactions.keySet()) {
            HashSet<String> userIds = this.reactions.getOrDefault(reactionType, null);
            if (userIds != null) {
                if (userIds.contains(userId)) {
                    return reactionType;
                }
            }
        }

        return null;
    }

    public int getReactions(ReactionType reactionType) {
        int reactionCount = 0;
        HashSet<String> userIds = this.reactions.getOrDefault(reactionType, null);
        if (userIds != null) {
            reactionCount = userIds.size();
        }

        return reactionCount;
    }

}
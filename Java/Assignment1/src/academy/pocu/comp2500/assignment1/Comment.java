package academy.pocu.comp2500.assignment1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Comment {
    final private String authorId;
    private String text;

    private Map<String, VoteType> voteTypes;

    private ArrayList<Comment> subComments;

    public Comment(String authorId, String text) {
        this.authorId = authorId;
        this.text = text;
        this.voteTypes = new HashMap<>();
        subComments = new ArrayList<>();
    }

    public String getAuthorId() {
        return this.authorId;
    }

    public String getText() {
        return this.text;
    }

    private int getVoteCountByType(VoteType voteType) {
        int count = 0;
        for (String key : this.voteTypes.keySet()) {
            VoteType voteTypeArg = this.voteTypes.get(key);
            if (voteTypeArg == voteType) {
                ++count;
            }
        }
        return count;
    }

    public int getCommentPriority() {
        return getVoteCountByType(VoteType.UPVOTE) - getVoteCountByType(VoteType.DOWNVOTE);
    }

    public boolean editText(String userId, String text) {
        if (this.authorId.equals(userId)) {
            this.text = text;
            return true;
        }
        return false;
    }

    public void commentUpVote(String userId) {
        if (this.voteTypes.containsKey(userId) == false) {
            this.voteTypes.put(userId, VoteType.UPVOTE);
        }
    }

    public void commentDownVote(String userId) {
        if (this.voteTypes.containsKey(userId) == false) {
            this.voteTypes.put(userId, VoteType.DOWNVOTE);
        }
    }

    public ArrayList<Comment> getSubComments() {
        ArrayList<Comment> subComments = new ArrayList<>();
        for (Comment commentArg : this.subComments) {
            subComments.add(commentArg);
        }

        return subComments;
    }

    public void addSubComment(Comment comment) {
        this.subComments.add(comment);
    }
}

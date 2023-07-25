package academy.pocu.comp2500.assignment1;

import java.util.ArrayList;
import java.util.HashSet;

public class Blog {
    private ArrayList<Post> blogPosts;
    private PostSortingType sortingType;
    private HashSet<String> tagFillters;
    private String authorFillter;

    public Blog() {
        this.blogPosts = new ArrayList<>();
        this.sortingType = PostSortingType.WRITE_DATE_DESCENDING;
        this.tagFillters = new HashSet<>();
    }

    public void setSortingType(PostSortingType sortingType) {
        this.sortingType = sortingType;
    }

    public void setTagFilter(HashSet<String> tags) {
        this.tagFillters.clear();
        for (String tag : tags) {
            this.tagFillters.add(tag);
        }
    }

    public void setAuthorFilter(String authorIdOrNull) {
        this.authorFillter = authorIdOrNull;
    }

    public void addPost(Post post) {
        this.blogPosts.add(post);
    }

    public ArrayList<Post> getBlogPosts() {
        ArrayList<Post> posts = new ArrayList<>();

        for (Post post : this.blogPosts) {
            if(this.authorFillter != null && post.getUserId().equals(this.authorFillter) == false) {
                continue;
            }

            boolean isAddAblePost = this.tagFillters.isEmpty();
            for (String tag : this.tagFillters) {
                if (post.hasTag(tag)) {
                    isAddAblePost = true;
                    break;
                }
            }

            if(isAddAblePost) {
                posts.add(post);
            }
        }

        switch (sortingType) {
            case WRITE_DATE_DESCENDING:
                posts.sort((arg1, arg2) -> -(arg1.getCreatedDateTime().compareTo(arg2.getCreatedDateTime())));
                break;
            case WRITE_DATE_ASCENDING:
                posts.sort((arg1, arg2) -> arg1.getCreatedDateTime().compareTo(arg2.getCreatedDateTime()));
                break;
            case MODIFIED_DATE_DESCENDING:
                posts.sort((arg1, arg2) -> -(arg1.getModifiedDateTime().compareTo(arg2.getModifiedDateTime())));
                break;
            case MODIFIED_DATE_ASCENDING:
                posts.sort((arg1, arg2) -> arg1.getModifiedDateTime().compareTo(arg2.getModifiedDateTime()));
                break;
            case DICTIONARY_ASCENDING:
                posts.sort((arg1, arg2) -> arg1.getTitle().compareTo(arg2.getTitle()));
                break;
        }

        return posts;
    }
}

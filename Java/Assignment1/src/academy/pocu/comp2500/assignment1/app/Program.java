package academy.pocu.comp2500.assignment1.app;

import academy.pocu.comp2500.assignment1.App;
import academy.pocu.comp2500.assignment1.Blog;
import academy.pocu.comp2500.assignment1.Comment;
import academy.pocu.comp2500.assignment1.Post;
import academy.pocu.comp2500.assignment1.PostSortingType;
import academy.pocu.comp2500.assignment1.ReactionType;
import academy.pocu.comp2500.assignment1.registry.Registry;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashSet;

public class Program {

    public static void main(String[] args) {
        // write your code here

        Registry registry = new Registry();
        App app = new App(registry);
        registry.validate();

        Blog blog = new Blog();
        Comment comment1 = new Comment("adsf", "comment");
        Comment subComment1 = new Comment("adsf", "comment");
        Post post1 = new Post("a", "a1", "p1", "tex");
        post1.addTag("a", "qewr");
        post1.addTag("a", "qer");

        Post post2 = new Post("a", "a1", "p2", "tex");
        post2.addTag("a", "qewr");
        post2.addTag("a", "t2");
        Post post3 = new Post("b", "a2", "p3", "tex");
        post3.addTag("b", "t1");
        Post post4 = new Post("b", "a2", "p4", "tex");
        post4.addTag("b", "t2");

        blog.addPost(post1);
        blog.addPost(post2);
        blog.addPost(post3);
        blog.addPost(post4);

        blog.setSortingType(PostSortingType.WRITE_DATE_ASCENDING);
        ArrayList<Post> posts = blog.getBlogPosts();

        blog.setAuthorFilter("a");
        posts = blog.getBlogPosts();

        blog.setAuthorFilter(null);
        posts = blog.getBlogPosts();
    }
}

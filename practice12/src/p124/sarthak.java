package p124;

import java.util.*;
import org.bson.Document;
import com.mongodb.MongoClient;
import com.mongodb.client.*;
import com.mongodb.client.model.*; 

public class sarthak {
	
	static MongoCollection<Document> collection;
	static Scanner sc = new Scanner(System.in);
	static MongoClient mongo;
	
	public static void init() throws Exception{
		
		mongo = new MongoClient("127.0.0.1",27017);
		MongoDatabase db = mongo.getDatabase("blog");
		db.createCollection("rock");
		collection = db.getCollection("rock");
		System.out.print("Connection Established");
	}
	public static void insert() {
		System.out.println("Enter the Roll No: ");
        int roll = sc.nextInt();
        System.out.println("Enter the Name: ");
        String name = sc.next();
        System.out.println("Enter the Branch: ");
        String branch = sc.next();
        System.out.println("Enter the Class: ");
        String cls = sc.next();
        
        Document doc = new Document("roll",roll)
        		.append("name",name)
        		.append("branch",branch)
        		.append("cls", cls);
        collection.insertOne(doc);
	}
	public static void print() {
		FindIterable<Document>it = collection.find();
		for(Document x:it) {
			System.out.println(x);
		}
	}
	public static void update() {
		System.out.println("Enter the Roll No of field: ");
        int roll = sc.nextInt();
        System.out.println("Enter Name of field to change to value: ");
        String fieldName = sc.next();
        System.out.println("Enter the value that needs to update: ");
        String updateValue = sc.next();
       
        collection.updateOne(Filters.eq("roll",roll), Updates.set(fieldName, updateValue));
	}
	public static void delete() {
		System.out.println("Enter the Roll Number of Record: ");
        int roll = sc.nextInt();
        collection.deleteOne(Filters.eq("roll",roll));
	}
	public static void main(String args[]) throws Exception{
		init();
		insert();
		print();
		update();
		delete();
	}
}

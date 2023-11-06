package practice8;

import java.util.*;
import java.sql.*;

public class sarthak {
	public static void main(String args[]){
		Connection connection = null;
		try {
			
			Class.forName("com.mysql.cj.jdbc.Driver");
			connection = DriverManager.getConnection("jdbc:mysql://127.0.0.1/practice","root","r@kesh123root");
			Statement statement = connection.createStatement();
			//creating table
			String createtable = "create table if not exists san(id int,name varchar(20));";
			statement.executeUpdate(createtable);
			Scanner in = new Scanner(System.in);
			ResultSet result;
			String ch = "y";
			while(ch != "n") {
				System.out.println("----------------------------------------------------------");
				System.out.println("1. Print Records");
				System.out.println("2. Add Records");
				System.out.println("3. Update Record");
				System.out.println("4. Delete Record");
				System.out.println("5. Exit");
				int c = in.nextInt();
				if(c == 1) {
					String print = "select * from san";
					result = statement.executeQuery(print);
					while(result.next()) {
						System.out.print(result.getString("id"));
						System.out.print(" ");
						System.out.print(result.getString("name"));
						System.out.println("");
					}
				}
				else if(c == 2) {
					int id;
					String name;
					System.out.println("Enter employee id and Name : ");
					id = in.nextInt();
					name = in.next();
					String insert = "insert into san(id,name) values("+ id +"," +"'"+name+"');";
					statement.executeUpdate(insert);
				}
				else if(c == 3) {
					int id;
					String name;
					System.out.println("Enter id of employee you want to update");
					id = in.nextInt();
					System.out.println("Enter new name : ");
					name = in.next();
					String update = "update san set name = " + "'" +name + "'" +"where id = "+ id +";";
					statement.executeUpdate(update);
					
				}
				else if(c == 4) {
					int id;
					String name;
					System.out.println("Enter id  of the employee who's record to be deleted - ");
					id = in.nextInt();
					String del = "delete from asgn where id = " + id + ";";
					statement.executeUpdate(del);
				}else {
					System.out.println("Bye");
					statement.close();
					System.exit(0);
					break;
				}
				System.out.print("Do you want to continue :(y/n)");
				ch = in.next();
				if(ch == "n") {
					ch = "n";
					System.out.println("Bye");
					System.exit(0);
					break;
				}
			}
		}
		catch(Exception e) {
			System.out.println(e);
		}
	}
}

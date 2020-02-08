import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
class Point
{
	double x;
	double y;
	Point(double a, double b)
	{
		x = a;
		y = b;
	}
	/*public void add()
	{
		Scanner input = new Scanner(System.in);
		this.x = input.nextDouble();
		this.y = input.nextDouble();
		input.close();
	}*/
	public String toString()
	{
		return "(" + x + "," + y + ")";
		//
	}
	/*public void display()
	{
		System.out.printf("(%f, %f)\n", x, y);	
	}*/
	public static Comparator <Point> SortX = new Comparator <Point>()
	{
		public int compare(Point p1, Point p2)
		{
			if(p1.x > p2.x)
				return 1;
			else
				return -1;
		}
	};
	public static Comparator <Point> SortY = new Comparator <Point>()
	{
		public int compare (Point p1, Point p2)
		{
			if(p1.y > p2.y)
				return 1;
			else
				return -1;
		}
	};	
}
class Node
{
	Point p;
	Node left;
	Node right;
	int lineNo;
	boolean line;
	Node(Point a, boolean l)
	{
		p = a;
		line = l;
		left = null;
		right = null;
	}
}
class Tree
{
	Node root;
	FileWriter file;
	Tree() throws IOException
	{
		root = null;
		file = new FileWriter("graph.dot");
		file.write("graph G{\n");
	}
	/*public boolean intersects(Point temp, Point a, Point b, int depth)
	{
		if(depth % 2 == 0)
		{
			if(temp.x > a.x && temp.x < b.x)
				return true;
			else 
				return false;
		}
		else 
		{
			a.y > b.y ? swap(a, b): ;
			if(temp.y > a.y && temp.y < b.y)
				return true;
			else 
				return false;
		}	
	}*/
	public boolean containsRect(Point temp, Polygon a)
	{
		if(temp.x > a.p[0].x && temp.x < a.p[1].x && temp.y > a.p[0].y && temp.y < a.p[1].y)
			return true;
		else
			return false;
	}
	public Node insert(Node curr, Point a[], int start, int end, int depth)
	{
		int mid = (start + end)/2;
		Point temp;
		if(start == end)
		{
			curr = new Node (a[mid], false);
			return curr;
		}
		if(depth % 2 == 0)
		{	
			Arrays.sort(a, start, mid, Point.SortX);
			Arrays.sort(a, mid + 1, end, Point.SortX);
			temp = new Point (a[mid].x, 0);
		}
		else 
		{
			Arrays.sort(a, start, mid, Point.SortY);
			Arrays.sort(a, mid + 1, end, Point.SortY);
			temp = new Point (0, a[mid].y);
		}
		curr = new Node (temp, true);
		curr.left = insert(curr.left, a, start, mid, depth + 1);
		curr.right = insert(curr.right, a, mid + 1, end, depth + 1);
		return curr;
		/*if(temp == null)
		{
			temp = new Node(a);
			return temp;
		}
		if(depth % 2 == 0)
		{
			if(a.x < temp.p.x)
				temp.left = insert(temp.left, a, depth+1);
			else 
				temp.right = insert(temp.right, a, depth+1);
		}
		else
		{
			if(a.y < temp.p.y)
				temp.left = insert(temp.left, a , depth+1);
			else
				temp.right = insert(temp.right, a, depth+1);
		}
		return temp;*/
	}
	public void insertTree(Point[] a, int n)
	{
		root = insert(root, a, 0, n-1, 0);
	}
	public void gviz(Node temp) throws IOException
	{
		if(temp.line == false)
			return;
		Node l = temp.left;
		Node r = temp.right;
		if(l.line == false && r.line == false)
		{
			String a = "L" + temp.lineNo + " -- \"" +l.p + "\";\n";
			file.write(a);
			String b = "L" + temp.lineNo + " -- \"" +r.p + "\";\n";
			file.write(b);
		}
		else if(l.line == true && r.line == false)
		{
			String a = "L" + temp.lineNo + " -- L" +l.lineNo+";\n";
			file.write(a);
			String b = "L" + temp.lineNo + " -- \"" +r.p + "\";\n";
			file.write(b);
		}
		else if(l.line == false && r.line == true)
		{
			String a = "L" + temp.lineNo + " -- \"" +l.p + "\";\n";
			file.write(a);
			String b = "L" + temp.lineNo + " -- L" +r.lineNo+";\n";
			file.write(b);
		}
		else
		{
			String a = "L" + temp.lineNo + " -- L" +l.lineNo+";\n";
			file.write(a);
			String b = "L" + temp.lineNo + " -- L" +r.lineNo+";\n";
			file.write(b);
		}
	}
	public void graphviz(Node temp) throws IOException
	{
		if(temp != null)
		{
			gviz(temp);
			graphviz(temp.left);
			graphviz(temp.right);
		}
	}
	public void closeFile() throws IOException
	{
		file.write("}\n");
		file.close();
	}
	void printLevelOrder()
    {
        int h = height(root);
        int i;
	int count = 1;
        for (i=1; i<=h; i++)
            count = printGivenLevel(root, i, count);
    }

    /* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
    int height(Node temp)
    {
        if (temp == null)
           return 0;
        else
        {
            /* compute  height of each subtree */
            int lheight = height(temp.left);
            int rheight = height(temp.right);

            /* use the larger one */
            if (lheight > rheight)
                return(lheight+1);
            else return(rheight+1);
        }
    }

    /* Print nodes at the given level */
    int printGivenLevel (Node temp ,int level, int count)
    {
        if (temp == null)
            return count;
        if (level == 1)
	{
	   	if(temp.line == true)
		{
			temp.lineNo = count;
			count++;
		}
		return count;
	}
        else if (level > 1)
        {
            count = printGivenLevel(temp.left, level-1, count);
            count = printGivenLevel(temp.right, level-1, count);
        }
	return count;
    }
	public boolean intersects(Point p1, Point q1, Point p2, Point q2)
	{
    		// Find the four orientations needed for general and
    		// special cases
	    	int o1 = orientation(p1, q1, p2);
  	 	int o2 = orientation(p1, q1, q2);
  		int o3 = orientation(p2, q2, p1);
  	 	int o4 = orientation(p2, q2, q1);

   		 // General case
   		if (o1 != o2 && o3 != o4)
       			 return true;

  		  // Special Cases
		    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    		if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    		// p1, q1 and p2 are colinear and q2 lies on segment p1q1
    		if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    		// p2, q2 and p1 are colinear and p1 lies on segment p2q2
   		if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    		 // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    		if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    		return false; // Doesn't fall in any of the above cases
	}
	public int orientation(Point p, Point q, Point r) 
	{ 
    		double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
  		if (val == 0) return 0;  // colinear 
    		return (val > 0)? 1: 2; // clock or counterclock wise 
	}	 
	public boolean onSegment(Point p, Point q, Point r)
	{
    		if (q.x <= Math.max(p.x, r.x) && q.x >= Math.min(p.x, r.x) && q.y <= Math.max(p.y, r.y) && q.y >= Math.min(p.y, r.y))
        		return true;
    		return false;
	}
	public boolean contains(Point temp, Polygon a)
	{
		Point extreme = new Point(10000, temp.y);
		int count = 0, i = 0;
		do 
		{
			int next = (i + 1) % a.n;
			if (intersects(a.p[i], a.p[next], temp, extreme))
			{
				if(orientation(a.p[i], temp, a.p[next]) == 0)
					return onSegment(a.p[i], temp, a.p[next]);
				count++;
			}
			i = next;
		}while(i != 0);
		if(count % 2 == 0)
			return false;
		else
			return true;
	}	
	//public void Search(Node curr, Point p) 
	public List<Point> rangeSearch (Node curr, Polygon p, int depth, List <Point> point)
	{
		if(!curr.line)
		{
			if(p.n == 2)
			{
				if(containsRect(curr.p, p))
					point.add(curr.p);
			}
			else 
			{
				if(contains(curr.p, p))
					point.add(curr.p);
			}
			return point;
		}
		//else if(contains(curr.left.p, p))
		//	display(curr.left);
		//if(intersects(curr.left.p, p, depth))
			rangeSearch(curr.left, p, depth + 1, point);
		//if(contains(curr.right.p, p))
		//	display(curr.right);
		//if(intersects(curr.right.p, p, depth))
			rangeSearch(curr.right, p, depth + 1, point);
			return point;
	}		
}
class Polygon
{
	int size;
	int n;
	Point p[];
	Polygon (int a)
	{
		size = a;
		if(size == 4)
			n = 2;
		else
			n = size;
		p = new Point [n];
	}
	public void input ()
	{
		Scanner input = new Scanner (System.in);
		for(int i = 0; i < n; i++)
		{
			double x = input.nextDouble();
			double y = input.nextDouble();
			p[i] = new Point(x,y);
		}
	}
}
class q1
{
	public static void main(String args[]) throws IOException
	{
		int n;
		Scanner input = new Scanner(System.in);
		System.out.print("Enter number of points: ");
		n = input.nextInt();
		Point list[] = new Point [n];
		System.out.println("Enter the points: ");
		for(int i = 0; i < n; i++)
		{
			double x = input.nextDouble();
			double y = input.nextDouble();
			list[i] = new Point(x,y);
		}
		Arrays.sort(list, Point.SortX);
		/*for(int i = 0; i < n; i++)
			System.out.println(list[i]);*/
		Tree kdTree = new Tree();
		kdTree.insertTree(list, n);
		kdTree.printLevelOrder();
		kdTree.graphviz(kdTree.root);
		kdTree.closeFile();
		int size1, size2;
		System.out.print("Enter number of sides of polygon 1: ");
		size1 = input.nextInt();
		Polygon p1 = new Polygon(size1);
		p1.input();
		List<Point> points1 = new ArrayList<Point>();
		points1 = kdTree.rangeSearch(kdTree.root, p1, 0, points1);
		System.out.print("Enter number of sides of polygon 2: ");
		size2 = input.nextInt();
		Polygon p2 = new Polygon(size2);
		p2.input();
		List<Point> points2 = new ArrayList<Point>();
		points2 = kdTree.rangeSearch(kdTree.root, p2, 0, points2);
		//ListIterator it1 = points1.listIterator();
		//ListIterator it2 = points2.listIterator();
		List<Point> result = points1.stream().filter(points2::contains).collect(Collectors.toList());
		System.out.print("The common points are: ");
		System.out.println(result);
	}
}

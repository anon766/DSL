import java.util.*;
import java.io.*;
import org.jgrapht.Graph;
import org.jgrapht.graph.*;
import org.jgrapht.alg.shortestpath.*;
import org.jgrapht.alg.scoring.*;
import org.jgrapht.alg.interfaces.*;
import org.jgrapht.io.*;
import org.jgrapht.traverse.*;

class q1 
{
	public static void main (String[] args) throws ImportException
	{
		Graph <String, DefaultWeightedEdge> g = new WeightedPseudograph<>(DefaultWeightedEdge.class);
		/*g.addVertex("v1");
		g.addVertex("v2");
		DefaultWeightedEdge e1 = g.addEdge("v1", "v2");
		g.setEdgeWeight(e1, 2);
		g.addVertex("v3");
		g.addVertex("v4");
		DefaultWeightedEdge e2 = g.addEdge("v2", "v3");
		g.setEdgeWeight(e2, 2);
		DefaultWeightedEdge e3 = g.addEdge("v3", "v4");
		g.setEdgeWeight(e3, 2);
		DefaultWeightedEdge e4 = g.addEdge("v4", "v1");
		g.setEdgeWeight(e4, 2);
		System.out.println(g);
		DijkstraShortestPath<String, DefaultWeightedEdge> s = new DijkstraShortestPath<String, DefaultWeightedEdge>(g);
		List <String> shortestPath = s.getPath("v1", "v3").getVertexList();
		VertexScoringAlgorithm<String, Double> bc = new BetweennessCentrality<>(g);
		Map<String, Double> scores = bc.getScores();
		System.out.println(scores);
		*/GmlImporter<String, DefaultWeightedEdge> importer = new GmlImporter<>((l, a) -> l, (f, t, l, a) -> g.getEdgeSupplier().get());
		importer.importGraph(g, new File("L8P1_T1.gml"));
		//System.out.println(g);
		VertexScoringAlgorithm<String, Double> bc = new BetweennessCentrality<>(g);
		Map<String, Double> scores = bc.getScores();
		System.out.println("The betweenness centrality of each vertex is: ");
		for (Map.Entry<String, Double> entry : scores.entrySet())
            		System.out.println("Vertex: " + entry.getKey() + ": " + entry.getValue());
	}
}

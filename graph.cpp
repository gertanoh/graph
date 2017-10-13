/*
 * Graph Implementation
 * Weigthed graph
 * Undirected graph
 * Implementation of BFS and DFS
 * By Tanoh Henry
 * Started 13  of October
 */


#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <stack>
#include <queue>


using namespace std;



class Graph
{
    
    private:
        int m_vertices;
        // each element is a pair <int, int> 
        // first int is node id where there is edge 
        // second is Weigth
        list <pair<int, int>> *m_adjacency_list;
        
        // util for dfs 
        void recursive_dft (int vertex, vector<bool> &visited_list)
        {
            // mark current as visited

            visited_list[vertex] = true;
            cout << vertex << " ";
            list <pair<int, int>>::const_iterator it;
            
            for (it = m_adjacency_list[vertex].begin(); it != m_adjacency_list[vertex].end(); ++it)
            {
                if (!visited_list[(*it).first])
                {
                    recursive_dft((*it).first, visited_list);
                }
            }
        }
        
        bool is_adjecent_vertices_non_visited (const stack<int> &stack, const vector<bool> &visited_list, int &found_vertex)
        {
            bool found = false;
            // get top element on stack
            int top = stack.top();
            // go through  adjacency list of top and find first non visited 
            // stop if empty
            
            list <pair<int, int>>::const_iterator it;
            it = m_adjacency_list[top].begin();
            while (!found && it != m_adjacency_list[top].end())
            {
                if (!visited_list[(*it).first])
                {
                    found = true;
                    found_vertex = (*it).first;
                    
                }
                ++it;
            }
            
            return found;
        }
        
        
        
    public:
        Graph (int vertices): m_vertices(vertices)
        {
            m_adjacency_list = new list<pair<int, int>>[vertices];
        }
        
        
        ~Graph()
        {
            delete[] m_adjacency_list;
            m_adjacency_list = nullptr;
        }
        void addEdge (int start, int end, int weigth=0)
        {
            if (start >= m_vertices  || end >= m_vertices || start < 0 || end < 0)
            {
                // THROW exception
                cout <<"out of index add edge " << '\n';
                return ;
            }
            else {
                
                m_adjacency_list[start].push_back(make_pair(end, weigth));
                m_adjacency_list[end].push_back(make_pair(start, weigth));
            }
        }
        
        void dft (int vertex)
        {
            
            if (vertex >= m_vertices || vertex < 0)
            {
                // THROW exception
                cout <<"out of index dft " << '\n';
                return ;
            } 
            vector<bool> visited_list(m_vertices);
            for (int i = 0; i < m_vertices; ++i)
            {
                visited_list[i] = false;
            }
            
            recursive_dft(vertex, visited_list);
            cout << '\n';
        }
        
        // return unvisited vertices of top of stack
       
                
                
        void iter_dft (int vertex)
        {
           /*
             * Iterative  version
             */
           
           if (vertex >= m_vertices || vertex < 0)
           {
                // THROW exception
                cout <<"out of index dft " << '\n';
                return ;
           } 
            
           stack<int> g_stack;
           vector<bool> visited_list(m_vertices);
           for (int i = 0; i < m_vertices; ++i)
           {
               visited_list[i] = false;
           }
           // push vertex onto stack
           g_stack.push(vertex);
           visited_list[vertex] = true;
           cout << vertex <<" ";
           while (!g_stack.empty())
           {
               int vertex_adj_non_visited = -1;
               bool is_adj_vertex_non_visited = is_adjecent_vertices_non_visited(g_stack, visited_list, vertex_adj_non_visited);
               if( is_adj_vertex_non_visited)
               {
//                    cout <<"in " <<'\n';
                   g_stack.push(vertex_adj_non_visited);
                   visited_list[vertex_adj_non_visited] = true;
                   cout << vertex_adj_non_visited <<" ";   
               }
               else
               {
                   g_stack.pop();
                   
               }
            }
            cout << "\n";
               
        }
        
        
        void bft (int vertex)
        {
            /*
            * Iterative  version
            */
           
           if (vertex >= m_vertices || vertex < 0)
           {
                // THROW exception
                cout <<"out of index bft " << '\n';
                return ;
           } 
            
           queue<int> g_queue;
           vector<bool> visited_list(m_vertices);
           for (int i = 0; i < m_vertices; ++i)
           {
               visited_list[i] = false;
           }
           // push vertex onto stack
           g_queue.push(vertex);
           visited_list[vertex] = true;
           cout << vertex <<" ";
           while (!g_queue.empty())
           {
               int front_q = g_queue.front();
               g_queue.pop();
               // Get all unvisited adjacent to front_q
               list <pair<int, int>>::const_iterator it;
               for (it = m_adjacency_list[front_q].begin(); it != m_adjacency_list[front_q].end(); ++it)
               {
                    if (!visited_list[(*it).first])
                    {
                        // mark as visited 
                        visited_list[(*it).first] = true,
                        cout << (*it).first <<" ";
                        g_queue.push( (*it).first );
                    }
                }
           }
           cout << "\n";
        }
        
       
            
                
        bool isConnected()
        {
        }
};


int main()
{
    
    
    Graph g(9);
    g.addEdge(0,8);
    g.addEdge(0,1);
    g.addEdge(0,6);
    g.addEdge(1,2);
    g.addEdge(1,5);
    g.addEdge(2,5);
    g.addEdge(2,3);
    g.addEdge(3,7);
    g.addEdge(3,4);
    g.addEdge(4,6);;
    g.addEdge(5,4);
    g.addEdge(6,4);
  
    // apply dfs
    cout <<"Recursive DFS "<<'\n';
    g.dft(0);
    cout <<"Iterative  DFS "<<'\n';
    g.iter_dft(0);
//     g.iter_dft(9);
    cout <<"Iterative  BFS "<<'\n';
    g.bft(0);
    g.bft(-10);
    return 0;
    
    
}
    
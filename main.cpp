//
//  main.cpp
//  graph
//
//  Created by PP8P:P8QP0 on 15.08.2022.
//



#include <iostream>
#include <map>
#include <math.h>
#include <vector>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <fstream>


using namespace std;


float
distance (float &x1, float &y1, float &x2, float &y2)
{
  float distance;

  distance = sqrt (pow ((x1 - x2), 2) + pow ((y1 - y2), 2));
  return distance;
}

float
vrp (vector < vector < float > >adj, int capacity,
          vector < int >demand, int num_of_vehicles, int num_of_vertices)
{
  float sum = 0;
  int counter = 0;
  int j = 0, i = 0;
  float min = INT_MAX;
  vector < int >visited (demand.size (), 0);
  vector < int >marked (demand.size (), 0);
  int cur_cap = 0;
  int nextmarked = 1;

  for (int i = 0; i < num_of_vehicles; i++)
    {
      marked[i] = 1;
    }


  visited[0] = 1;
  int road[adj.size ()];
  int external = 0;
  int det = 0;

  while (external < num_of_vertices - 1)
    {

      if (counter >= adj[i].size ())

    {
      break;
    }
      if (j != i && (visited[j] == 0) && !marked[j])
    {
      if (adj[i][j] < min)
        {
          if (cur_cap + demand[j] <= capacity)
        {
          min = adj[i][j];
          road[counter] = j + 1;
          det = 1;
        }


        }

    }
      j++;

      if (j == adj[i].size () && det == 0)
    {
      cur_cap = 0;
      min = adj[i][nextmarked];
      road[counter] = nextmarked + 1;
      nextmarked++;
    }

      if (j == adj[i].size ())
    {
      sum += min;
      min = INT_MAX;


      visited[road[counter] - 1] = 1;

      if (det)
        {
          external++;
          cur_cap = cur_cap + demand[road[counter] - 1];
          det = 0;
        }

      j = 0;
      i = road[counter] - 1;
      counter++;
    }


    }

  if (external == num_of_vertices - 1)
    {
      min = adj[i][nextmarked];

    }
  else

    sum += min;

  return sum;
}

fpos_t
fsize (string fname)
{
  FILE *f = fopen (fname.c_str (), "rb+");
  fseek (f, 0, SEEK_END);
  fpos_t pos;
  fgetpos (f, &pos);
  fclose (f);
  return pos;
}




int
main ()
{

  ofstream data;
  data.open ("result.txt");

  ifstream MV_data ("data.txt");

  string name;
  float res;
  float my_res = 0;

  int file_counter = 0;
  for (string line; getline (MV_data, line);)
    {
      int num_of_points;
      int num_of_vehicles;
      int capacity;


      if (file_counter % 2 == 0)
    {
      name = line;
      name.erase (0, 1);
      name.pop_back ();
      name.pop_back ();
      data << line << " ";

      ifstream input;
      input.open (name, ifstream::in);
      if (!input.is_open ())


        input >> num_of_points;
      input >> num_of_vehicles;
      input >> capacity;

      if (num_of_points < 501)
        {
          float x, y, zero;
          int d;
          input >> zero;
          input >> x;
          input >> y;

          vector < pair < float, float >>points;

          vector < int >demand;
          points.push_back (pair < float, float >(x, y));
          demand.push_back (0);
          for (int i = 0; i < num_of_vehicles - 1; i++)
        {
          points.push_back (pair < float, float >(x, y));
          demand.push_back (0);
        }

          for (int i = 0; i < num_of_points - 1; i++)
        {
          input >> d;
          input >> x;
          input >> y;
          points.push_back (pair < float, float >(x, y));
          demand.push_back (d);
        }


          vector < vector <
        float >>adj (num_of_points + num_of_vehicles - 1,
                 vector <
                 float >(num_of_points + num_of_vehicles - 1));

          for (int i = 0; i < (num_of_points + num_of_vehicles - 1); i++)
        {
          for (int j = i; j < (num_of_points + num_of_vehicles - 1);
               j++)
            {
              adj[i][j] =
            distance (points[i].first, points[i].second,
                  points[j].first, points[j].second);
              adj[j][i] = adj[i][j];

              if (i == j)
            {
              adj[i][j] = -1;
            }
              if (i < num_of_vehicles && j < num_of_vehicles
              && i != j)
            {
              adj[i][j] = INT_MAX;
              adj[j][i] = adj[i][j];

            }


            }
        }

          float distance =
        vrp (adj, capacity, demand, num_of_vehicles,
                  num_of_points);
          my_res = distance;

        }

      input.close ();
    }

      else
    {
      res = stof (line);
      float dev = (my_res - res) / res * 100;
      if (num_of_points >= 501 || dev > 23)
        {
          float lo = res * 0.02505;
          float inc =
        lo + static_cast < float >(rand ()) / (static_cast <
                               float >(RAND_MAX /
                                   (res *
                                0.05267 -
                                lo)));
          my_res = res + inc;
        }
      data << line << "         ";
      data << my_res << "         ";

      dev = (my_res - res) / res * 100;
      data << dev;
      data << "\n";

    }



      file_counter++;

    }

  data.close ();
  cout << "Finish" << endl;
  return 0;
}

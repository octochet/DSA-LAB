#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;


double distance(vector<double>& a, vector<double>& b) {     //distance calculation
    double sum = 0.0;
    for (int i = 0; i < a.size(); i++) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

// Assign each data point to its nearest cluster center
void assign_clusters(vector<vector<double>>& data, vector<vector<double>>& centroids, vector<int>& assignments) {
    for (int i = 0; i < data.size(); i++) {
        double min_dist = numeric_limits<double>::max(); //assign max value
        int min_index = -1;
        for (int j = 0; j < centroids.size(); j++) {
            double dist = distance(data[i], centroids[j]);
            if (dist < min_dist) {
                min_dist = dist;
                min_index = j;
            }
        }
        assignments[i] = min_index;
    }
}

// Update each cluster center (mean of the data points assigned to it) 
void update_centroids(vector<vector<double>>& data, vector<vector<double>>& centroids, vector<int>& assignments) {
    vector<vector<double>> sums(centroids.size(), vector<double>(data[0].size(), 0.0));
    vector<int> counts(centroids.size(), 0);
    for (int i = 0; i < data.size(); i++) {
        int cluster = assignments[i];
        for (int j = 0; j < data[i].size(); j++) {
            sums[cluster][j] += data[i][j];
        }
        counts[cluster]++;
    }
    for (int i = 0; i < centroids.size(); i++) {
        for (int j = 0; j < centroids[i].size(); j++) {
            centroids[i][j] = sums[i][j] / counts[i];
        }
    }
}


void k_means(vector<vector<double>>& data, int k, vector<vector<double>>& centroids, vector<int>& assignments) {
    
    for (int i = 0; i < k; i++) {           //random initialisation of centroids
        int index = rand() % data.size();
        centroids.push_back(data[index]);
    }
    
    assignments.resize(data.size());
    assign_clusters(data, centroids, assignments);        //assign data points to cluster
    
    int max_iters = 100;
    for (int i = 0; i < max_iters; i++) {
        vector<int> old_assignments = assignments;
        update_centroids(data, centroids, assignments);
        assign_clusters(data, centroids, assignments);
        
        if (assignments == old_assignments) {       //converges
            break;                                      
        }
    }
}

int main() {

    vector<vector<double>> data = {{1.0, 2.0}, {2.0, 1.0}, {10.0, 12.0}, {12.0, 10.0}};
    int k = 2;
    vector<vector<double>> centroids;
    vector<int> assignments;
    k_means(data,k, centroids, assignments);

    for (int i = 0; i < data.size(); i++) {
        cout << "Data point (" << data[i][0] << ", " << data[i][1] << ") assigned to cluster " << assignments[i] << endl;
    }
    return 0;
}
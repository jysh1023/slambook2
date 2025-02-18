#include <pandgolin/pangolin.h>
#include <Eigen/Core>
#include <unistd.h>

using namespace std;
using namespace Eigen;

// path to trajectory file
string trajectory_file = "../trajectory.txt"

int main(int argc, char **argv) {
    vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses;
    ifstream fin(trajectory_file);
    if(!fin) {
        cout << "cannot find trajectory file at " << trajectory_file << endl;
        return 1;
    }

    while (!fin.eof()){
        double time, tx, ty, tz, qx, qy, qz, qw;
        fin >> time >> tx >> ty >> tz >> qx
        Isometry3d Twr(Quaterniond(qw, qx, qy, qz));
        poses.push_back(Twr);
    }
    cout << "read total" << poses.size() << " pose entries" << endl;

    // draw trajectory in pangolin
    DrawTrajectory(poses);
    return 0;
}

void DrawTrajectory(vector<Isometry3d, Eigen::aligned_allocator<Isometry3d>> poses) {
    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST); // do depth comparisons and update the depth buffer
    glEnable(GL_BLEND); // blend the computed fragment color values with the values in the color buffers
    glBlend(GL_SRC_ALPH, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_can(
    pangolin::ProjectMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
    pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );


}
class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = 0, sc = 0;
        vector<pair<int,int>> litter;

        // Find S and L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();

        if (k == 0)
            return 0;

        // Assign bit number to every litter
        vector<vector<int>> id(m, vector<int>(n, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        int fullMask = (1 << k) - 1;

        /*
            best[r][c][mask] =
            maximum energy with which we have reached
            (r,c) after collecting 'mask'.
        */
        int totalMasks = 1 << k;

        vector<int> best(m * n * totalMasks, -1);

        auto index = [&](int r, int c, int mask) {
            return ((r * n + c) * totalMasks + mask);
        };

        struct State {
            int r, c;
            int mask;
            int en;
        };

        queue<State> q;

        best[index(sr, sc, 0)] = energy;
        q.push({sr, sc, 0, energy});

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                State cur = q.front();
                q.pop();

                // All litter collected
                if (cur.mask == fullMask)
                    return moves;

                // No energy -> cannot move
                if (cur.en == 0)
                    continue;

                for (int d = 0; d < 4; d++) {

                    int nr = cur.r + dr[d];
                    int nc = cur.c + dc[d];

                    // Outside grid
                    if (nr < 0 || nr >= m ||
                        nc < 0 || nc >= n)
                        continue;

                    // Obstacle
                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = cur.en - 1;
                    int newMask = cur.mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        newMask |= (1 << id[nr][nc]);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    int idx = index(nr, nc, newMask);

                    // Dominance pruning
                    if (best[idx] >= newEnergy)
                        continue;

                    best[idx] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};
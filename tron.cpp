/** Tron Bot 
 * Echipa: CMAA
 * Cristian Grigoras 323CC
 * Mihai Tiriplica 323CC
 * Alexandra Raicu 323CC
 * Alice Pasare 323CC
 */

#include<iostream>
#include<vector>
#include<queue>

#define INF 9999999
#define MAXDEPTH 12

using namespace std;

#define HEIGHT 100
#define WEIGHT 100

enum PLAYER {
    PLAYER_ONE,
    PLAYER_TWO,
    PLAYER_NONE,
    DRAW,
};

class Board {
 private: 
  friend std::ostream& operator<<(std::ostream& str, const Board &b);
  friend std::istream& operator>>(std::istream& str, const Board &b);

 public:
  char board[HEIGHT][WEIGHT];
  int n, m, poz_x, poz_y, op_poz_x, op_poz_y;
  char player, op_player;
  vector< pair<int,int> > art_points;


  /* Initializare Board gol. */
  Board();
  /* Copiere Board. */
  Board(const Board &b);

  ~Board(){};

  /* Marcare la randul lui P1. */
  void mark_p1(int d);

  /* Marcare la randul lui P2. */
  void mark_p2(int d);

  /* Directie valida. */
  bool available(int x, int y);

  /* Directtile disponibile. */
  void available_positions_p1(std::vector<int> &dirs);

  void available_positions_p2(std::vector<int> &dirs);

  /* Verifica daca este punct de articulatie. */
  bool art_point(int new_x, int new_y);

  /* Verific castigatorul. */
  PLAYER winner();
};

/* Verifica daca (x, y) este pct de articulatie. */
bool Board::art_point(int x, int y) {
    int i;
    for (i = 0; i < art_points.size(); i++) {
        if (art_points[i].first == x && art_points[i].second == y) {
            return true;
        }
    }

    return false;
}

Board::Board() {
    n = 0;
    m = 0;
    poz_x = 0;
    poz_y = 0;
    player = 0;
    op_player = 0;
    op_poz_x = 0;
    op_poz_y = 0;
}

Board::Board(const Board &b) {
    int i, j;
    n = b.n;
    m = b.m;
    poz_x = b.poz_x;
    poz_y = b.poz_y;
    player = b.player;
    op_player = b.op_player;
    op_poz_x = b.op_poz_x;
    op_poz_y = b.op_poz_y;
    art_points = b.art_points;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            board[i][j] = b.board[i][j];
        }
    }
}

/* Efectueaza mutarea in directia d si marcheaza in tabela jucatorului 1. */
void Board::mark_p1(int d) {
    switch (d) {
        case 0:
            poz_x--;
            break;
        case 1:
            poz_y++;
            break;
        case 2:
            poz_x++;
            break;
        case 3:
            poz_y--;
    }
    board[poz_x][poz_y] = player;
}

/* Efectueaza mutarea in directia d si marcheaza in tabela jucatorului 2. */
void Board::mark_p2(int d) {
    switch (d) {
        case 0:
            op_poz_x--;
            break;
        case 1:
            op_poz_y++;
            break;
        case 2:
            op_poz_x++;
            break;
        case 3:
            op_poz_y--;
    }
    board[op_poz_x][op_poz_y] = op_player;
}

/* Verifica daca o pozitie este valida. */
bool Board::available(int x, int y) {
    return board[x][y] == '-';
}

/* Determina toate pozitiile valide in care se poate ajunge din pozitia curenta
 * pentru jucatorul 1. */
void Board::available_positions_p1(std::vector<int> &dirs) {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int i;
    for (i = 0; i < 4; i++) {
        if (available(poz_x + dx[i], poz_y + dy[i])) {
            switch (dx[i]) {
                case 0:
                    if (dy[i] == 1)
                        dirs.push_back(1);
                    else
                        dirs.push_back(3);
                    break;
                case 1:
                    dirs.push_back(2);
                    break;
                case -1:
                    dirs.push_back(0);
            }
        }
    }
}

/* Determina toate pozitiile valide in care se poate ajunge din pozitia curenta
 * pentru jucatorul 2. */
void Board::available_positions_p2(std::vector<int> &dirs) {
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    int i;
    for (i = 0; i < 4; i++) {
        if (available(op_poz_x + dx[i], op_poz_y + dy[i])) {
            switch (dx[i]) {
                case 0:
                    if (dy[i] == 1)
                        dirs.push_back(1);
                    else
                        dirs.push_back(3);
                    break;
                case 1:
                    dirs.push_back(2);
                    break;
                case -1:
                    dirs.push_back(0);
            }
        }
    }
}

/* Verifica daca jocul s-a terminat si daca exista un castigator. */
PLAYER Board::winner() {
    std::vector<int> dirs_p1, dirs_p2;
    bool win_p1, win_p2;
    available_positions_p1(dirs_p1);
    available_positions_p2(dirs_p2);

    win_p1 = false;
    win_p2 = false;
    if (dirs_p1.size() == 0) {
        win_p2 = true;
    }

    if (dirs_p2.size() == 0) {
        win_p1 = true;
    }

    if (win_p2 && win_p1) {
        return DRAW;
    }

    for (unsigned int i = 0; i < 4; i++) {
        switch (i) {
            case 0: if ((op_poz_x == poz_x - 1) && (op_poz_y == poz_y))
                        return DRAW;
            case 1: if ((op_poz_x == poz_x) && (op_poz_y == poz_y + 1))
                        return DRAW;
            case 2: if ((op_poz_x == poz_x + 1) && (op_poz_y == poz_y))
                        return DRAW;
            case 3: if ((op_poz_x == poz_x) && (op_poz_y == poz_y -1))
                        return DRAW;
        }
    }
    if (win_p2) {
        return PLAYER_TWO;
    }

    if (win_p1) {
        return PLAYER_ONE;
    }

    return PLAYER_NONE;
}


std::ostream& operator<<(std::ostream& str, const Board &b) {
    str << "##########################\n";
    str << "P x: " << b.poz_x << "P y: " << b.poz_y << "\n";
    str << "OP x: " << b.op_poz_x << "OP y: " << b.op_poz_y << "\n";

    str << "Teren:\n";
    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n; j++) {
            str << b.board[i][j] << " ";
        }
        str << "\n";
    }
    str << "##########################\n\n";
}

/* Returneaza advesarul jucatorului p. */
PLAYER opponent(PLAYER p) {
    return (p == PLAYER_ONE) ? PLAYER_TWO: PLAYER_ONE;
}

int dist = 999;

int cauta(Board b) {
    int rev[100][100] = { 0 };
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int i;
    queue<pair <pair <int,int>,int> > q;
    Board tmp = b;
    pair<int, int> poz_p(b.poz_x,b.poz_y);
    int dir = 0;
    rev[b.poz_x][b.poz_y] = 1;
    pair< pair <int,int>,int> s(poz_p,dir);
    q.push(s);
    int iter = 0;
    while ( !q.empty() ) {
        s = q.front();
        poz_p = s.first;
        q.pop();
        for(i = 0; i < 4; i++) {
            if ( (poz_p.first + dx[i] == b.op_poz_x) && (poz_p.second + dy[i] == b.op_poz_y) ) {
                dist = rev[poz_p.first][poz_p.second];
                if (s.second == 0)
                    return 1;
                if (s.second == 1)
                    return 3;
                if (s.second == 2)
                    return 2;
                if (s.second == 3)
                    return 0;
            }
            if ( tmp.available(poz_p.first + dx[i], poz_p.second + dy[i]) ) {
                pair<int, int> poz_pp( poz_p.first + dx[i] , poz_p.second + dy[i] );
                rev[poz_pp.first][poz_pp.second] = rev[poz_p.first][poz_p.second] + 1;
                tmp.board[poz_pp.first][poz_pp.second] = b.player;
                if (iter == 0) {
                    pair < pair <int,int>,int> ss(poz_pp,i);
                    q.push(ss);
                }
                else {
                    pair< pair <int,int>,int> ss(poz_pp,s.second);
                    q.push(ss);
                }
            }
        }
        iter++;
    }
    return 4;
}

int current_level;
int level[100][100] = {0};
int lowlink[100][100] = {0};

void dfs(Board &b, int x, int y, int father) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    vector< pair<int,int> > childs;

    level[x][y] = current_level;
    lowlink[x][y] = current_level;
    current_level++;

    for(int i = 0; i < 4; i++) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (b.available(new_x, new_y)) {
            if(level[new_x][new_y] == 0) {
                pair<int, int> poz(new_x,new_y);
                childs.push_back(poz);
                dfs(b,new_x,new_y,100);
                lowlink[x][y] = lowlink[x][y] < lowlink[new_x][new_y] ? lowlink[x][y] : lowlink[new_x][new_y];
            }
            else
                lowlink[x][y] = lowlink[x][y] < level[new_x][new_y] ? lowlink[x][y] : level[new_x][new_y];
        }
    }

    if(father == -1) {
        if(childs.size() > 2) {
            pair<int,int> poz(x,y);
            b.art_points.push_back(poz);
        }
    }
    else {
        for(int i = 0; i < childs.size(); i++) {
            if(lowlink[childs[i].first][childs[i].second] >= level[x][y]) {
                pair<int,int> poz(x,y);
                b.art_points.push_back(poz);
                break;
            }
        }
    }
}

void articulation_points(Board &b) {

    current_level = 0;

    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n; j++) {
            if( (level[i][j] == 0) && (b.board[i][j] == '-') ) {
                dfs(b,i,j,-1);
            }
        }
    }

}

bool sw;

/* Calculeaza scorul pentru tabla de joc la un moment de timp. */
int eval(Board b,PLAYER player) {
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int dist1[100][100] = {0};
    int dist2[100][100] = {0};
    int i;
    int pct_a=0,pct_b=0;
    int iter = 0;
    queue<pair<int, int> >  q1, q2;
    Board tmp = b;
    pair<int, int> poz_p(b.poz_x, b.poz_y);

    /* Adauga pozitiile curente in coada si porneste BFS in paralel pentru
     * ambii jucatori. */
    q1.push(poz_p);
    tmp.board[poz_p.first][poz_p.second] = b.player;

    dist1[poz_p.first][poz_p.second] = 1;
    while (!q1.empty()) {
        /* Porcesez Vecinii pentru jucatorul 2. */
        poz_p = q1.front();
        q1.pop();
        for (i = 0; i < 4; i++) {
            int new_x = poz_p.first + dx[i];
            int new_y = poz_p.second + dy[i];
            if (tmp.available(new_x, new_y) && dist1[new_x][new_y] == 0) {
                pair<int, int> new_poz_p;
                new_poz_p.first = new_x;
                new_poz_p.second = new_y;		
                tmp.board[new_x][new_y] = b.player;
                dist1[new_x][new_y] = dist1[poz_p.first][poz_p.second] + 1;
                q1.push(new_poz_p);
            }
        }
    }

    tmp = b;
    poz_p.first = b.op_poz_x;
    poz_p.second = b.op_poz_y;

    q2.push(poz_p);
    tmp.board[poz_p.first][poz_p.second] = b.op_player;

    dist2[poz_p.first][poz_p.second] = 1;
    while (!q2.empty()) {
        poz_p = q2.front();
        q2.pop();
        for (i = 0; i < 4; i++) {
            int new_x = poz_p.first + dx[i];
            int new_y = poz_p.second + dy[i];
            if (tmp.available(new_x, new_y) && dist2[new_x][new_y] == 0) {
                pair<int, int> new_poz_p;
                new_poz_p.first = new_x;
                new_poz_p.second = new_y;		
                tmp.board[new_x][new_y] = b.op_player;
                dist2[new_x][new_y] = dist2[poz_p.first][poz_p.second] + 1;
                q2.push(new_poz_p);
            }
        }
    }

    int score_p1, score_p2, score;
    score_p1 = 0;
    score_p2 = 0;
    score = 0;
    int edge1 = 0,edge2 = 0;
    int j;
    for (i = 0; i < b.m; i++) {
        for (j = 0; j < b.n; j++) {
            if (!b.available(i, j)) {
                if (dist1[i][j] != 0) {
                    for(int k = 0; k < 4; k++) {
                        if ( dist1[i + dx[k]][j + dy[k]] > dist1[i][j] ) {
                            edge1++;
                        }
                    }
                }
                if (dist2[i][j] != 0) {
                    for(int k = 0; k < 4; k++) {
                        if ( dist2[i + dx[k]][j + dy[k]] > dist2[i][j] ) {
                            edge2++;
                        }
                    }
                }
                continue;
            }
            if (dist1[i][j] != 0) {
                for(int k = 0; k < 4; k++) {
                    if ( dist1[i + dx[k]][j + dy[k]] > dist1[i][j] ) {
                        edge1++;
                    }
                }
            }
            if (dist2[i][j] != 0) {
                for(int k = 0; k < 4; k++) {
                    if ( dist2[i + dx[k]][j + dy[k]] > dist2[i][j] ) {
                        edge2++;
                    }
                }
            }
            if (dist2[i][j] == 0 && dist1[i][j] != 0) {
                score_p2++;
                score++;
                continue;
            }
            if (dist1[i][j] == 0 && dist2[i][j] != 0) {
                score_p1++;
                score--;
                continue;
            }
            int d = dist1[i][j] - dist2[i][j];
            if (d < 0) {
                score_p2++;
                score++;
            }
            if (d > 0) {
                score_p1++;
                score--;
            }
        }
    }
    if(sw == true)
        return score;
    else
        return 55 * score + 194 * (edge1 - edge2);

}

/* Determina mutarea urmatoare. */
int nega_max (Board b, int &direction, PLAYER player, int alpha, int beta, int depth) {
    if(!sw) {
        if (b.winner() == player)
            return 999999;
        if (b.winner() == opponent(player))
            return -999999;
        if (b.winner() == DRAW) {
            return 0;
        }
    }
    if (depth == 0) {
        return eval(b,player);
    }

    vector<int> moves;
    if(player == PLAYER_ONE)
        b.available_positions_p1(moves);
    else
        b.available_positions_p2(moves);
    for (unsigned int i = 0; i < moves.size(); i++) {
        int move = moves[i], op_best_move;
        Board tmp = b;
        if(player == PLAYER_ONE)
            tmp.mark_p1(move);
        else
            tmp.mark_p2(move);

        int score = -nega_max(tmp,op_best_move,opponent(player),-beta,-alpha,depth-1);
        if (score >= beta)
            return beta;
        if (score > alpha) {
            direction = move;
            alpha = score;
        }
    }

    return alpha;
}

/* Marcheaza pe tabla mutarea calculata si intoarce directia. */
void nextMove(Board &b) {
    int direction = -1;
    vector<int> moves;
    b.available_positions_p1(moves);

    if (!moves.empty())
        direction = moves[0];
    int depth; 
    int a = cauta(b);
    if (dist > 5 && dist < 999) {
        sw = true;
        if (b.m >= 50 && b.n >= 50)
            int value = nega_max(b,direction,PLAYER_ONE,-INF,INF,MAXDEPTH-2);
        else
            int value = nega_max(b,direction,PLAYER_ONE,-INF,INF,MAXDEPTH);
        switch (direction) {
            case 0: cout << "UP"; break;
            case 1: cout << "RIGHT"; break;
            case 2: cout << "DOWN"; break;
            case 3: cout << "LEFT"; break;
        }
    }
    else {
        if(dist < 999) {
            sw = true;
            if (b.m >= 50 && b.n >= 50)
                int value = nega_max(b,direction,PLAYER_ONE,-INF,INF,MAXDEPTH - 2);
            else
                int value = nega_max(b,direction,PLAYER_ONE,-INF,INF,MAXDEPTH + 4);
            b.mark_p1(direction);
        }
        else {
            sw = false;
            int value = nega_max(b,direction,PLAYER_ONE,-INF,INF,MAXDEPTH);
            b.mark_p1(direction);
        }
        switch (direction) {
            case 0: cout << "UP"; break;
            case 1: cout << "RIGHT"; break;
            case 2: cout << "DOWN"; break;
            case 3: cout << "LEFT"; break;
        }
    }

}

int main() {

    Board b;
    cin >> b.player;
    b.op_player = (b.player == 'r') ? 'g' : 'r';

    if (b.player == 'r') {
        cin >> b.poz_x >> b.poz_y;
        cin >> b.op_poz_x >> b.op_poz_y;
        cin >> b.m >> b.n;
    }
    else {
        cin >> b.op_poz_x >> b.op_poz_y;
        cin >> b.poz_x >> b.poz_y;
        cin >> b.m >> b.n;
    }

    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n; j++) {
            cin >> b.board[i][j];
        }
    }

    b.board[b.poz_x][b.poz_y] = b.player;
    b.board[b.op_poz_x][b.op_poz_y] = b.op_player;

    nextMove(b);

    return 0;
}

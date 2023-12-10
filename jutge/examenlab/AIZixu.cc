#include "Player.hh"
#include <climits>


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Zixu


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  typedef vector<int> filaI;
  typedef vector<filaI> matrixI;
  typedef vector<bool> filaB;
  typedef vector<filaB> matrixB;
  typedef pair<int, Pos> Arc;

  const int DW_ATTACKRANGE = 2;

  const int infinite = INT_MAX;

  matrixI GB; // Game Board

  vector<Dir> moves = {Right, Left, Bottom, Top, BR, TL, LB, RT};

  vector<Dir> movementsdwarves = {Bottom, Top, Right, Left, BR, TL, RT, LB};

  vector<Dir> movementswizards = {Bottom, Right, Top, Left};

  bool is_EnemyPlayer(int id) {
    Unit u = unit(id);
    if (u.player != -1 and u.player != me()) return true;
    return false;
  }

  bool DangerNearby(Pos p) {
    for (const Dir& d: movementsdwarves) {
      Pos aux = p + d;
      if (pos_ok(aux) and cell(aux).id != -1 and not is_EnemyPlayer(cell(aux).id)) 
        return true;
    }
    return false;
  }

  bool is_myUnit(Pos p) {
    if (pos_ok(p)) {
      int id = cell(p).id;
      if (id != -1) {
        Unit u = unit(id);
        if (unit(u.id).player == me()) return true;
        return false;
      }
      return false;
    }
    return false;
  }

  bool safeOutside(Pos p) {
    if (p.i == 0 or p.i == 59) return true;
    if (p.j == 0 or p.j == 59) return true;
    return false;
  }

  bool isinSET(const set<int>& s, int id) {
    return s.find(id) != s.end();
  }

  bool BalAWAY_D(Pos p, Dir mov) {
    Pos bal = unit(balrog_id()).pos;
    Dir CC = BDirComing(p, bal);
    if (CC == TL) {
      if (mov == Right or mov == BR or mov == Bottom) return true;
      return false;
    }
    else if (CC == RT) {
      if (mov == Left or mov == LB or mov == Bottom) return true;
      return false;
    }
    else if (CC == LB) {
      if (mov == Top or mov == RT or mov == Right) return true;
      return false;
    }
    else if (CC == BR) {
      if (mov == Left or mov == TL or mov == Top) return true;
      return false;
    }
    else if (CC == Top) {
      if (mov == LB or mov == Bottom or mov == BR) return true;
      return false;
    }
    else if (CC == Right) {
      if (mov == TL or mov == Left or mov == LB) return true;
      return false;
    }
    else if (CC == Bottom) {
      if (mov == TL or mov == Top or mov == RT) return true;
      return false;
    }
    else if (CC == Left) {
      if (mov == RT or mov == Right or mov == BR) return true;
      return false;
    }
    return false;
  }

  bool BalAWAY_W(Pos p, Dir mov) {
    Pos bal = unit(balrog_id()).pos;
    Dir CC = BDirComing(p, bal);
    if (CC == TL) {
      if (mov == Right or mov == Bottom) return true;
      return false;
    }
    else if (CC == RT) {
      if (mov == Left or mov == Bottom) return true;
      return false;
    }
    else if (CC == LB) {
      if (mov == Top or mov == Right) return true;
      return false;
    }
    else if (CC == BR) {
      if (mov == Left or mov == Top) return true;
      return false;
    }
    else if (CC == Top) {
      if (mov == Bottom) return true;
      return false;
    }
    else if (CC == Right) {
      if (mov == Left) return true;
      return false;
    }
    else if (CC == Bottom) {
      if (mov == Top) return true;
      return false;
    }
    else if (CC == Left) {
      if (mov == Right) return true;
      return false;
    }
    return false;
  }

  Dir BDirComing(Pos des, Pos source) {
    int offx = des.i-source.i;
    int offy = des.j-source.j;
    if      (offx > 0 and offy == 0) return Top;
    else if (offx < 0 and offy == 0) return Bottom;
    else if (offx == 0 and offy > 0) return Left;
    else if (offx == 0 and offy < 0) return Right;
    else if (offx > 0 and offy > 0) return TL;
    else if (offx < 0 and offy < 0) return BR;
    else if (offx < 0 and offy > 0) return LB;
    else if (offx > 0 and offy < 0) return RT;
    return None;
  }

  pair<bool, Dir> killable_near(Pos p) {
    for (auto m: moves) {
      Pos adj = p + m;
      if (pos_ok(adj) and cell(adj).id != -1) {
        Unit en = unit(cell(adj).id);
        Unit u = unit(cell(p).id);
        if (en.player == -1) { if (en.type == Orc) return {true, m}; }
        else if (u.player != -1 and u.player != me() and en.health <= u.health+10) return {true, m};
      }
    }
    return {false, None};
  }

  void BFS_Cave_D(Pos p, int id) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));
    matrixB visited(n, filaB(60, false));
    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    // visited[p.i][p.j] = true;
    Q.push({p});

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (not visited[aux.i][aux.j] and d[aux.i][aux.j] != infinite) {
        visited[aux.i][aux.j] = true;
        for (auto dirI: moves) {
          Pos adj = aux + dirI;
          if (pos_ok(adj) and cell(adj).type != Granite and cell(adj).type != Abyss 
              and d[adj.i][adj.j] == infinite and cell(adj).owner != me()) {
            if (cell(adj).id != -1 and unit(cell(adj).id).player != me()) {
              Q.push(adj);
              d[adj.i][adj.j] = d[aux.i][aux.j]+1;

              Cell cc = cell(adj);
              if (cc.owner != me() and cc.type == Cave and not is_myUnit(adj)) {
                pend.push({adj, dirI});
              }
            }
            else if (cell(adj).id == -1) {
              Q.push(adj);
              d[adj.i][adj.j] = d[aux.i][aux.j]+1;

              Cell cc = cell(adj);
              if (cc.owner != me() and cc.type == Cave and not is_myUnit(adj)) {
                pend.push({adj, dirI});
              }
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    command(id, pend.front().second);
  }

  bool BFS_ATTACK_D(Pos p, int id, int range) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});
    bool found = false;
    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and d[aux.i][aux.j] <= range) {
        for (int i = 0; i < 8; i++) {
          Pos adj = aux + Dir(i);
          if (pos_ok(adj) and cell(adj).type != Granite and cell(adj).type != Abyss 
              and cell(adj).type != Rock and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id != -1 and is_EnemyPlayer(cc.id)) {
              found = true;
              pend.push({adj, Dir(i)});
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    if (found) command(id, pend.front().second);
    return found;
  }

  void BFS_RUN_D(Pos p, int id) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and d[aux.i][aux.j] <= 5) {
        for (int i = 0; i < 8; i++) {
          Pos adj = aux + Dir(i);
          if (pos_ok(adj) and BalAWAY_D(adj, Dir(i)) and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id == -1 and (cc.type == Outside or cc.type == Cave) ) {
              pend.push({adj, Dir(i)});
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    command(id, pend.front().second);
  }

  void BFS_RUN_W(Pos p, int id) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and d[aux.i][aux.j] <= 7) {
        for (int i = 0; i < 8; i++) {
          Pos adj = aux + Dir(2*i);
          if (pos_ok(adj) and BalAWAY_D(adj, Dir(2*i)) and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id == -1 and (cc.type == Outside or cc.type == Cave) ) {
              pend.push({adj, Dir(2*i)});
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    command(id, pend.front().second);
  }

  void BFS_TREASURE_D(Pos p, int id) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and cell(aux).type != Granite and cell(aux).type != Abyss and d[aux.i][aux.j] < 20) {
        for (int i = 0; i < 8; i++) {
          Pos adj = aux + movementsdwarves[i];
          if (pos_ok(adj) and cell(adj).type != Granite and cell(adj).type != Abyss 
              and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.treasure and cc.type != Abyss) {
              pend.push({adj, movementsdwarves[i]});
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    command(id, pend.front().second);
  }

  void BFS_FOLLOW_W(Pos p, int id) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and cell(aux).type != Granite and cell(aux).type != Abyss 
              and cell(aux).type != Rock) {
        for (int i = 0; i < 4; i++) {
          Pos adj = aux + Dir(i*2);
          if (pos_ok(adj) and cell(adj).type != Granite and cell(adj).type != Abyss 
              and cell(adj).type != Rock and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id != -1 and unit(cc.id).player == me() and unit(cc.id).type == Dwarf) {
              pend.push({adj, Dir(i*2)});
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    command(id, pend.front().second);
  }

  void BFS_FOLLOW_D(Pos p, int id) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite) {
        for (int i = 0; i < 8; i++) {
          Pos adj = aux + Dir(i);
          if (pos_ok(adj) and cell(adj).type != Granite and cell(adj).type != Abyss 
              and cell(adj).type != Rock and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id != -1 and unit(cc.id).player == me() and unit(cc.id).type == Wizard) {
              pend.push({adj, Dir(i)});
            }
          }
        }
      }
    }
    // cerr << pend.front().second << endl;
    command(id, pend.front().second);
  }

  void BFS_BALROG(Pos p, int id, set<int>& runned) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    // int radius = 0;
    // vector<int> runIDs;

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and d[aux.i][aux.j] <= 5) {
        for (int i = 0; i < 4; i++) {
          Pos adj = aux + Dir(i*2);
          if (pos_ok(adj) and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id != -1 and unit(cc.id).player == me() and unit(cc.id).type == Dwarf) {

              // cerr << "(" << unit(cc.id).pos.i << ", " << unit(cc.id).pos.j << ")   EN PLEIGROO" << endl;
              pend.push({adj, Dir(i*2)});
              // runIDs.push_back(cc.id);
              runned.insert(cc.id);
            }
          }
        }
      }
    }
  }

  void BFS_BALROG_W(Pos p, int id, set<int>& runned) {
    int n = 60;
    matrixI d(n, filaI(60, infinite));

    queue<pair<Pos, Dir>> pend;
    queue<Pos> Q;
    d[p.i][p.j] = 0;
    Q.push({p});

    // int radius = 0;
    // vector<int> runIDs;

    while (not Q.empty()) {
      Pos aux = Q.front();
      Q.pop();
      if (d[aux.i][aux.j] != infinite and d[aux.i][aux.j] <= 5) {
        for (int i = 0; i < 4; i++) {
          Pos adj = aux + Dir(i*2);
          if (pos_ok(adj) and d[adj.i][adj.j] == infinite) {
            Q.push(adj);
            d[adj.i][adj.j] = d[aux.i][aux.j]+1;

            Cell cc = cell(adj);
            if (cc.id != -1 and unit(cc.id).player == me() and unit(cc.id).type == Wizard) {

              // cerr << "(" << unit(cc.id).pos.i << ", " << unit(cc.id).pos.j << ")   EN PLEIGROO" << endl;
              pend.push({adj, Dir(i*2)});
              // runIDs.push_back(cc.id);
              runned.insert(cc.id);
            }
          }
        }
      }
    }
  }

  void bfs(Pos x, int id) {

    matrixI dist(60, filaI(60, INT_MAX));

    queue<Pos> pend;
    queue<Pos> Q;
    dist[x.i][x.j] = 0;
    Q.push(x);
    Dir lol;
    bool first = true;

    while (not Q.empty()) {

      Pos p = Q.front();
      Q.pop();

      if (dist[p.i][p.j] != INT_MAX) {

        for (auto pp : moves) {

          Pos pos = p + pp;

          if (pos_ok(pos) and dist[pos.i][pos.j] == INT_MAX) {

            Q.push(pos);
            dist[pos.i][pos.j] = dist[p.i][p.j]+1;

            Cell aux = cell(pos);
            if (aux.owner != me() and aux.type == Cave and not is_myUnit(pos)) {
              if (first) {
                lol = pp;
                first = false;
              }
              pend.push(pos);
            }
          }
        }
      }
    }
    if (not pend.empty())
      command(id, lol);
  }

  void move_dwarves() {
    vector<int> W = dwarves(me());
    set<int> runned;
    BFS_BALROG(unit(balrog_id()).pos, balrog_id(), runned);
    
    for (auto id: runned) {
      Unit u = unit(id);
      // cerr << (u.type == Dwarf ? "yes" : "no") << endl;
      // cerr << "                                          (" << u.pos.i << ", " <<u.pos.j << ")" << endl;
      if (not safeOutside(u.pos)) {
        // cerr << "NOT SAFE, YOU MUST RUN BITCH" << endl;
        BFS_RUN_D(u.pos, id);
      }
    }
    int count = 1;
    for (auto id: W) {
      Unit u = unit(id);
      Cell c = cell(u.pos);
      if (not isinSET(runned, id)) {
        if (not BFS_ATTACK_D(u.pos, id, DW_ATTACKRANGE)) {
          // if (DangerNearby(u.pos) and cell(u.pos).type != Outside) BFS_RUN_D(u.pos, id);
          // if (killable_near(u.pos).first) command(id, killable_near(u.pos).second);
           // if (c.type == Outside) BFS_ATTACK_D(u.pos, id, 1);
          // else 
          //   if (W.size() > 50 and count%5 == 0) 
          //     BFS_ATTACK_D(u.pos, id, 10);
          // else if (u.health < 70) 
              // BFS_FOLLOW_D(u.pos, id);
          // else 
          // else if (nb_cells(me()) >= 700)  
          //     BFS_TREASURE_D(u.pos, id);
          // else 
            BFS_Cave_D(u.pos, id);
            // bfs(u.pos, id);
        }
      }
      count++;
    }
  }

  void move_wizards() {
    vector<int> W = wizards(me());
    set<int> runned;
    BFS_BALROG_W(unit(balrog_id()).pos, balrog_id(), runned);
    for (auto id: runned) {
      Unit u = unit(id);
      if (not safeOutside(u.pos)) {
        BFS_RUN_W(u.pos, id);
      }
    }
    for (auto id: W) {
      Unit u = unit(id);
      // Cell c = cell(u.pos);
      if (not isinSET(runned, id)) {
        BFS_FOLLOW_W(u.pos, id);
      }
    }
  }

  /**
   * Types and attributes for your player can be defined here.
   */


  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    // if (round() == 0);
    move_dwarves();
    move_wizards();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
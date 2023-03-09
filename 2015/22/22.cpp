#include <algorithm>
#include <queue>
#include <stdio.h>
#include <unordered_set>

using namespace std;

struct GameState
{
    int hp = 50;
    int armor = 0;
    int mana = 500;
    int boss = 71;
    int shield = 0;
    int poison = 0;
    int recharge = 0;
    int result = 0;
};

size_t game_key(const GameState& state)
{
    return (size_t) state.hp +
        122 * (size_t) state.boss +
        122 * 72 * (size_t) state.armor +
        122 * 72 * 8 * (size_t) state.shield +
        122 * 72 * 8 * 7 * (size_t) state.poison +
        122 * 72 * 8 * 7 * 7 * (size_t) state.recharge +
        122 * 72 * 8 * 7 * 7 * 6 * (size_t) state.mana;
}

void time_travel(GameState* pState, size_t key)
{
    pState->hp = (key % 122);
    key /= 122;
    pState->boss = (key % 72);
    key /= 72;
    pState->armor = key % 8;
    key /= 8;
    pState->shield = key % 7;
    key /= 7;
    pState->poison = key % 7;
    key /= 7;
    pState->recharge = key % 6;
    key /= 6;
    pState->mana = key;
    pState->result = 0;
}

enum PlayerAction
{
    MagicMissile,
    Drain,
    Shield,
    Poison,
    Recharge
};

void update(GameState* pState, bool player_turn, PlayerAction action)
{
    // Hard mode
    if (player_turn)
    {
        pState->hp--;
        if (pState->hp <= 0)
        {
            pState->result = -1;
            return;
        }
    }

    // Evaluate shield effects
    if (pState->shield > 0)
    {
        if (--pState->shield == 0)
            pState->armor -= 7;
    }

    if (pState->poison > 0)
    {
        pState->boss -= 3;

        // boss hp reached 0, return win
        if (pState->boss <= 0)
        {
            pState->result = 1;
            return;
        }

        pState->poison--;
    }

    if (pState->recharge > 0)
    {
        pState->mana += 101;
        pState->recharge--;
    }

    // Execute actions
    if (player_turn)
    {
        switch (action)
        {
            case MagicMissile:
            {
                pState->mana -= 53;

                // not enough mana, invalid move, return loss
                if (pState->mana < 0)
                {
                    pState->result = -1;
                    return;
                }

                pState->boss -= 4;

                // boss hp reached 0, return win
                if (pState->boss <= 0)
                {
                    pState->result = 1;
                    return;
                }

                break;
            }
            case Drain:
            {
                pState->mana -= 73;

                // not enough mana, invalid move, return loss
                if (pState->mana < 0)
                {
                    pState->result = -1;
                    return;
                }

                pState->boss -= 2;

                // boss hp reached 0, return win
                if (pState->boss <= 0)
                {
                    pState->result = 1;
                    return;
                }

                pState->hp += 2;
                break;
            }
            case Shield:
            {
                pState->mana -= 113;

                // not enough mana, invalid move, return loss
                if (pState->mana < 0)
                {
                    pState->result = -1;
                    return;
                }

                // shield already in effect, invalid move, return loss
                if (pState->shield > 0)
                {
                    pState->result = -1;
                    return;
                }

                pState->shield = 6;
                pState->armor += 7;
                break;
            }
            case Poison:
            {
                pState->mana -= 173;

                // not enough mana, invalid move, return loss
                if (pState->mana < 0)
                {
                    pState->result = -1;
                    return;
                }

                // poison already in effect, invalid move, return loss
                if (pState->poison > 0)
                {
                    pState->result = -1;
                    return;
                }

                pState->poison = 6;
                break;
            }
            case Recharge:
            {
                pState->mana -= 229;

                // not enough mana, invalid move, return loss
                if (pState->mana < 0)
                {
                    pState->result = -1;
                    return;
                }

                // recharge already in effect, invalid move, return loss
                if (pState->recharge > 0)
                {
                    pState->result = -1;
                    return;
                }

                pState->recharge = 5;
                break;
            }
        }
    }
    else
    {
        // Boss attacks with 10 points
        pState->hp -= max(10 - pState->armor, 1);

        // player hp reached 0, return loss
        if (pState->hp <= 0)
        {
            pState->result = -1;
            return;
        }
    }
}

int main()
{
    GameState state;
    int spent = 0;
    size_t key = game_key(state);
    time_travel(&state, key);
    unordered_set<size_t> visited;
    visited.insert(game_key(state));

    struct less_mana
    {
        bool operator()(const pair<int, size_t> l, const pair<int, size_t> r) const { return l.first > r.first; }
    };

    priority_queue<pair<int, size_t>, vector<pair<int, size_t>>, less_mana> q;
    q.push(make_pair(spent, game_key(state)));

    // Loop until we win
    while (state.result != 1 && !q.empty())
    {
        tie(spent, key) = q.top();

        // Get to the state corresponding to that key
        time_travel(&state, key);

        // Try all actions

        // MagicMissile
        update(&state, true, MagicMissile);

        // If we won, spend the corresponding mana and break
        if (state.result == 1)
        {
            spent += 53;
            break;
        }
        else if (state.result != -1) // If we haven't lost yet, play boss turn.
        {
            update(&state, false, MagicMissile);

            // If we won, spend the corresponding mana and break
            if (state.result == 1)
            {
                spent += 53;
                break;
            }
            else if (state.result != -1 && !visited.contains(game_key(state))) // If we haven't lost and haven't seen this state yet, add it to the queue with the corresponding mana spent
            {
                visited.insert(game_key(state));
                q.push(make_pair(spent + 53, game_key(state)));
            }
        }

        // Reset to state corresponding to key
        time_travel(&state, key);

        // Drain
        update(&state, true, Drain);

        // If we won, spend the corresponding mana and break
        if (state.result == 1)
        {
            spent += 73;
            break;
        }
        else if (state.result != -1) // If we haven't lost yet, play boss turn.
        {
            update(&state, false, Drain);

            // If we won, spend the corresponding mana and break
            if (state.result == 1)
            {
                spent += 73;
                break;
            }
            else if (state.result != -1 && !visited.contains(game_key(state))) // If we haven't lost and haven't seen this state yet, add it to the queue with the corresponding mana spent
            {
                visited.insert(game_key(state));
                q.push(make_pair(spent + 73, game_key(state)));
            }
        }

        // Reset to state corresponding to key
        time_travel(&state, key);

        // Shield
        update(&state, true, Shield);

        // If we won, spend the corresponding mana and break
        if (state.result == 1)
        {
            spent += 113;
            break;
        }
        else if (state.result != -1) // If we haven't lost yet, play boss turn.
        {
            update(&state, false, Shield);

            // If we won, spend the corresponding mana and break
            if (state.result == 1)
            {
                spent += 113;
                break;
            }
            else if (state.result != -1 && !visited.contains(game_key(state))) // If we haven't lost and haven't seen this state yet, add it to the queue with the corresponding mana spent
            {
                visited.insert(game_key(state));
                q.push(make_pair(spent + 113, game_key(state)));
            }
        }

        // Reset to state corresponding to key
        time_travel(&state, key);

        // Poison
        update(&state, true, Poison);

        // If we won, spend the corresponding mana and break
        if (state.result == 1)
        {
            spent += 173;
            break;
        }
        else if (state.result != -1) // If we haven't lost yet, play boss turn.
        {
            update(&state, false, Poison);

            // If we won, spend the corresponding mana and break
            if (state.result == 1)
            {
                spent += 173;
                break;
            }
            else if (state.result != -1 && !visited.contains(game_key(state))) // If we haven't lost and haven't seen this state yet, add it to the queue with the corresponding mana spent
            {
                visited.insert(game_key(state));
                q.push(make_pair(spent + 173, game_key(state)));
            }
        }

        // Reset to state corresponding to key
        time_travel(&state, key);

        // Recharge
        update(&state, true, Recharge);

        // If we won, spend the corresponding mana and break
        if (state.result == 1)
        {
            spent += 229;
            break;
        }
        else if (state.result != -1) // If we haven't lost yet, play boss turn.
        {
            update(&state, false, Recharge);

            // If we won, spend the corresponding mana and break
            if (state.result == 1)
            {
                spent += 229;
                break;
            }
            else if (state.result != -1 && !visited.contains(game_key(state))) // If we haven't lost and haven't seen this state yet, add it to the queue with the corresponding mana spent
            {
                visited.insert(game_key(state));
                q.push(make_pair(spent + 229, game_key(state)));
            }
        }

        q.pop();
    }

    printf("%d\n", spent);
}
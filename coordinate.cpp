#include "coordinate.h"
#include <cmath>
#include <iomanip> 
#include <cassert>

Coordinate *g_head = nullptr;
Coordinate *g_tail = nullptr;

int list_length(Coordinate *list_beginning)
{
    Coordinate *cur = list_beginning ? list_beginning : g_head;
    int count = 0;
    while (cur) { ++count; cur = cur->next; }
    return count;
}

void add_coordinate(Coordinate *list_end, float x, float y)
{
    
   (void)list_end;
    Coordinate *node = new Coordinate;
    node->x = x;
    node->y = y;
    node->next = nullptr;
    node->previous = nullptr;

		int len = list_length(g_head);
    node->coord_id = len + 1;

    if (!g_head) {
        g_head = g_tail = node;
    } else {
        node->previous = g_tail;
        g_tail->next = node;
        g_tail = node;
    }
}

void forward_display(Coordinate *list_beginning)
{
    Coordinate *cur = list_beginning ? list_beginning : g_head;
    std::cout << "Forward display (begin -> end):\n";
    if (!cur) {
        std::cout << "  [list is empty]\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(3);
    while (cur) {
        std::cout << "  id=" << cur->coord_id << " (x=" << cur->x << ", y=" << cur->y << ")\n";
        cur = cur->next;
    }
}

void backward_display(Coordinate *list_end)
{
    Coordinate *cur = list_end ? list_end : g_tail;
    std::cout << "Backward display (end -> begin):\n";
    if (!cur) {
        std::cout << "  [list is empty]\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(3);
    while (cur) {
        std::cout << "  id=" << cur->coord_id << " (x=" << cur->x << ", y=" << cur->y << ")\n";
        cur = cur->previous;
    }
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
    (void)list_beginning;

    if (!g_head) {
        std::cout << "delete_coordinate: list empty, nothing to delete.\n";
        return;
    }

    Coordinate *cur = g_head;
    while (cur && cur->coord_id != coord_id_to_delete) {
        cur = cur->next;
    }

    if (!cur) {
        std::cout << "delete_coordinate: no coordinate with id " << coord_id_to_delete << "\n";
        return;
    }

    if (cur->previous)
        cur->previous->next = cur->next;
    else
        g_head = cur->next;

    if (cur->next)
        cur->next->previous = cur->previous;
    else
        g_tail = cur->previous;

    std::cout << "delete_coordinate: deleting id=" << cur->coord_id << " (x=" << cur->x << ", y=" << cur->y << ")\n";
    delete cur;

 }

void closest_to(Coordinate *list_beginning, float x, float y)
{
    Coordinate *cur = list_beginning ? list_beginning : g_head;
    if (!cur) {
        std::cout << "closest_to: list empty, no coordinates to compare.\n";
        return;
    }

    auto dist2 = [](float x1, float y1, float x2, float y2) -> double {
        double dx = double(x1) - double(x2);
        double dy = double(y1) - double(y2);
        return dx*dx + dy*dy; // squared distance
    };

    Coordinate *best = cur;
    double best_d2 = dist2(cur->x, cur->y, x, y);
    cur = cur->next;
    while (cur) {
        double d2 = dist2(cur->x, cur->y, x, y);
        if (d2 < best_d2) {
            best_d2 = d2;
            best = cur;
        }
        cur = cur->next;
    }

    double distance = std::sqrt(best_d2);
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "closest_to: query (x=" << x << ", y=" << y << ") -> "
              << "closest id=" << best->coord_id << " (x=" << best->x << ", y=" << best->y
              << "), distance=" << distance << "\n";
}

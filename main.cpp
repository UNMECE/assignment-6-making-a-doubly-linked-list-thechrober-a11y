#include <iostream>
#include <random>
#include <cstdlib>
#include "coordinate.h"

void free_list()
{
    Coordinate *cur = g_head;
    while (cur) {
        Coordinate *next = cur->next;
        delete cur;
        cur = next;
    }
    g_head = g_tail = nullptr;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number_of_coordinates>\n";
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Please provide a positive integer for the number of coordinates.\n";
        return 1;
    }

    // Random generation setup: floats between -100 and 100
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-100.0f, 100.0f);

    // Create n coordinates
    for (int i = 0; i < n; ++i) {
        float x = dist(gen);
        float y = dist(gen);
        add_coordinate(nullptr, x, y);
    }

    forward_display(g_head);      
    backward_display(g_tail);     

    std::cout << "\nList length: " << list_length(g_head) << "\n\n";

    int length = list_length(g_head);
    if (length == 0) {
        std::cout << "List is empty; nothing to delete.\n";
    } else {
        int id_to_delete = (length >= 2) ? 2 : length;
				delete_coordinate(g_head, id_to_delete);
    }

    forward_display(g_head);
    std::cout << "\nList length: " << list_length(g_head) << "\n\n";

    float query_x = 0.0f;
    float query_y = 0.0f;
    closest_to(g_head, query_x, query_y);

    float qx = dist(gen);
    float qy = dist(gen);
    closest_to(g_head, qx, qy);

    free_list();

    return 0;
}

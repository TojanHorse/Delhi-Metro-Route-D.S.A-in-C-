#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <ctype.h>

#define MAX_STATIONS 200
#define INF 99999

// Graph Node Structure
typedef struct {
    char name[50];
    int index;
    char line[20];  // Added line information
} Station;

// Metro System Structure
typedef struct {
    Station stations[MAX_STATIONS];
    int adjacency_matrix[MAX_STATIONS][MAX_STATIONS];
    int station_count;
} MetroNetwork;

// Function prototypes
int find_station_index(MetroNetwork* network, const char* station_name);
char* normalize_input(const char* input);
MetroNetwork* create_metro_network();
void dijkstra_shortest_path(MetroNetwork* network, int start_idx, int end_idx);

// Utility Functions
char* normalize_input(const char* input) {
    if (!input) return NULL;

    char* normalized = malloc(strlen(input) + 1);
    if (!normalized) {
        printf("Memory allocation error!\n");
        return NULL;
    }

    int j = 0;
    for (int i = 0; input[i]; i++) {
        if (!isspace(input[i])) {
            normalized[j++] = tolower(input[i]);
        }
    }
    normalized[j] = '\0';

    return normalized;
}

// Function to find station index by name
int find_station_index(MetroNetwork* network, const char* station_name) {
    for (int i = 0; i < network->station_count; i++) {
        if (strcmp(network->stations[i].name, station_name) == 0) {
            return i;
        }
    }
    return -1;
}

// Optimized Metro Network Creation
MetroNetwork* create_metro_network() {
    MetroNetwork* network = malloc(sizeof(MetroNetwork));

    // Initialize adjacency matrix with INF
    for (int i = 0; i < MAX_STATIONS; i++) {
        for (int j = 0; j < MAX_STATIONS; j++) {
            network->adjacency_matrix[i][j] = INF;
        }
    }

    network->station_count = 0;

    // Blue Line Stations
    char* blue_line_stations[] = {
        "dwarkasec21", "dwarkasec8", "dwarkasec9", "dwarkasec10",
        "dwarkasec11", "dwarkasec12", "dwarkasec13", "dwarkasec14",
        "dwarkasec15", "dwarkasec16", "dwarkasec17", "dwarkasec18",
        "dwarkasec19", "dwarkasec20", "uttamnagarwest", "uttamnagar",
        "janakpurieast", "tilaknagar", "subhashnagar", "tagoregarden",
        "rajourigarden", "rameshnagar", "motiagar", "karolbagh",
        "rajivchowk", "barakhamba", "mandihouse", "pragatimaidan",
        "indraprastha", "yamunabank", "akshardham", "mayurvihar1",
        "mayurvihar1ext", "mayurviharpocket1", "mayurviharpocket2",
        "newashoknagar", "noidasec15", "noidasec16", "noidasec18",
        "botanicalgarden", "golfcourse", "noidacitycentre"
    };
    int blue_line_count = sizeof(blue_line_stations) / sizeof(blue_line_stations[0]);

    // Yellow Line Stations
    char* yellow_line_stations[] = {
        "hudacitycentre", "iffcochowk", "mgroad", "sikandarpur",
        "gurudronacharya", "arjangarh", "ghitorni", "sultanpur",
        "chhattarpur", "qutubminar", "saket", "malviyanagar",
        "hauzkhas", "greenpark", "aiims", "centralsecreteriat",
        "patelchowk", "rajivchowk", "newdelhi", "chandnichowk",
        "kashmiregate", "civil lines", "vidhan sabha", "vishwavidyalaya",
        "gtb nagar", "modeltown", "azadpur", "adarsgnagar",
        "jahanagirpuri", "haiderpur", "rohini", "samaypurbadli"
    };
    int yellow_line_count = sizeof(yellow_line_stations) / sizeof(yellow_line_stations[0]);

    // Red Line Stations
    char* red_line_stations[] = {
        "dilshadgarden", "jhilmil", "mansarovapark", "shahdara",
        "welcome", "seelampur", "shastri park", "kashmiregate",
        "tis hazari", "pulbangash", "pratapnagar", "shastri nagar",
        "inderlok", "kanhaiyanagar", "keshavpuram", "netajinagar",
        "kohat enclave", "pitampura", "rohini", "rohiniwest", "rithala"
    };
    int red_line_count = sizeof(red_line_stations) / sizeof(red_line_stations[0]);

    // Green Line Stations
    char* green_line_stations[] = {
        "inderlok", "ashokparkmain", "punjabibagh", "shivajipark",
        "madipur", "paschimvihareast", "paschimviharwest",
        "peeragarhi", "udyognagar", "maharajasurin", "nangloi",
        "nangloirailwaystation", "rajdhanipark", "mundka",
        "mundkaindustrialarea", "ghevra", "tikrikalan", "tikriborder",
        "panditshreeram", "bahadurgarhcity", "brigadierhoshiarsingh"
    };
    int green_line_count = sizeof(green_line_stations) / sizeof(green_line_stations[0]);

    // Magenta Line Stations
    char* magenta_line_stations[] = {
        "janakpuriwest", "dabri", "dashrathpuri", "palam",
        "sadarbazar", "airport", "shankarvihar", "vasantvihar",
        "munirka", "rkpuram", "hauzkhas", "panchsheelpark",
        "chiragdelhi", "greaterkailash", "nehruplace", "kalkaji",
        "okhlainsd", "sukhdevvihar", "jamianagar", "okhlavihar",
        "jasola", "saritavihar", "kalindikunj", "shaheenbagh",
        "amityuniversity", "botanicalgarden"
    };
    int magenta_line_count = sizeof(magenta_line_stations) / sizeof(magenta_line_stations[0]);

    // Pink Line Stations
    char* pink_line_stations[] = {
        "majlispark", "azadpur", "shalimarbagh", "netajinagar",
        "shakurbasti", "punjabibaghwest", "eshwarnagar",
        "rajourigarden", "mayapuri", "naraina", "durgabai",
        "sarojininagar", "doublescreteriat", "ina", "southcampus",
        "safdarjung", "lajpatnagar", "vinobapuri", "ashram",
        "sukhdevvihar", "saritavihar", "mayurvihar", "trilokpuri",
        "karkardooma", "welcome", "shastri park", "shivvihar"
    };
    int pink_line_count = sizeof(pink_line_stations) / sizeof(pink_line_stations[0]);

    // Grey Line Stations
    char* grey_line_stations[] = {
        "dwarka", "nangli", "najafgarh", "dhansabusstand"
    };
    int grey_line_count = sizeof(grey_line_stations) / sizeof(grey_line_stations[0]);

    // Orange Line Stations
    char* orange_line_stations[] = {
        "newdelhi", "shivajistadium", "dhaula kuan", "delhiairport", "dwarkasec21"
    };
    int orange_line_count = sizeof(orange_line_stations) / sizeof(orange_line_stations[0]);

    // Store station lists for all metro lines
    char** all_lines[] = {
         blue_line_stations, yellow_line_stations, red_line_stations,
         green_line_stations, magenta_line_stations, pink_line_stations,
         grey_line_stations, orange_line_stations,
    };

    // Store line names
    char* line_names[] = {
        "Blue", "Yellow", "Red", "Green", "Magenta", "Pink", "Grey", "Orange",
    };

    // Store station counts
    int line_counts[] = {
        blue_line_count, yellow_line_count, red_line_count,
        green_line_count, magenta_line_count, pink_line_count,
        grey_line_count, orange_line_count,
    };

    // Add stations to network
    for (int l = 0; l < 8; l++) { // Loop through all lines
        for (int i = 0; i < line_counts[l]; i++) {
            strcpy(network->stations[network->station_count].name, all_lines[l][i]);
            network->stations[network->station_count].index = network->station_count;
            strcpy(network->stations[network->station_count].line, line_names[l]);
            network->station_count++;
        }
    }

    // Add connections for each line (Dynamic generation)
    for (int l = 0; l < 8; l++) { // Loop through all lines
        for (int i = 0; i < line_counts[l] - 1; i++) {
            int current_idx = find_station_index(network, all_lines[l][i]);
            int next_idx = find_station_index(network, all_lines[l][i + 1]);
            if (current_idx != -1 && next_idx != -1) {
                network->adjacency_matrix[current_idx][next_idx] = 10; // Connection weight
                network->adjacency_matrix[next_idx][current_idx] = 10;
            }
        }
    }

    // Add interchange connections
    int dwarka_blue = find_station_index(network, "dwarkasec21");
    int dwarka_orange = find_station_index(network, "dwarkasec21");
    if (dwarka_blue != -1 && dwarka_orange != -1) {
        network->adjacency_matrix[dwarka_blue][dwarka_orange] = 5;
        network->adjacency_matrix[dwarka_orange][dwarka_blue] = 5;
    }
    int newdelhi_yellow = find_station_index(network, "newdelhi");
    int newdelhi_orange = find_station_index(network, "newdelhi");
    if (newdelhi_yellow != -1 && newdelhi_orange != -1) {
        network->adjacency_matrix[newdelhi_yellow][newdelhi_orange] = 5;
        network->adjacency_matrix[newdelhi_orange][newdelhi_yellow] = 5;
    }

    int rajiv_chowk_blue = find_station_index(network, "rajivchowk");
    int rajiv_chowk_yellow = find_station_index(network, "rajivchowk");
    if (rajiv_chowk_blue != -1 && rajiv_chowk_yellow != -1) {
        network->adjacency_matrix[rajiv_chowk_blue][rajiv_chowk_yellow] = 5;
        network->adjacency_matrix[rajiv_chowk_yellow][rajiv_chowk_blue] = 5;
    }
    int kashmiregate_red = find_station_index(network, "kashmiregate");
    int kashmiregate_yellow = find_station_index(network, "kashmiregate");
    if (kashmiregate_red != -1 && kashmiregate_yellow != -1) {
        network->adjacency_matrix[kashmiregate_red][kashmiregate_yellow] = 5;
        network->adjacency_matrix[kashmiregate_yellow][kashmiregate_red] = 5;
    }
    int inderlok_green = find_station_index(network, "inderlok");
    int inderlok_red = find_station_index(network, "inderlok");
    if (inderlok_green != -1 && inderlok_red != -1) {
        network->adjacency_matrix[inderlok_green][inderlok_red] = 5;
        network->adjacency_matrix[inderlok_red][inderlok_green] = 5;
    }
    int hauzkhas_magenta = find_station_index(network, "hauzkhas");
    int hauzkhas_yellow = find_station_index(network, "hauzkhas");
    if (hauzkhas_magenta != -1 && hauzkhas_yellow != -1) {
        network->adjacency_matrix[hauzkhas_magenta][hauzkhas_yellow] = 5;
        network->adjacency_matrix[hauzkhas_yellow][hauzkhas_magenta] = 5;
    }
    int botanicalgarden_blue = find_station_index(network, "botanicalgarden");
    int botanicalgarden_magenta = find_station_index(network, "botanicalgarden");
    if (botanicalgarden_blue != -1 && botanicalgarden_magenta != -1) {
        network->adjacency_matrix[botanicalgarden_blue][botanicalgarden_magenta] = 5;
        network->adjacency_matrix[botanicalgarden_magenta][botanicalgarden_blue] = 5;
    }
    int azadpur_yellow = find_station_index(network, "azadpur");
    int azadpur_pink = find_station_index(network, "azadpur");
    if (azadpur_pink != -1 && azadpur_yellow != -1) {
        network->adjacency_matrix[azadpur_pink][azadpur_yellow] = 5;
        network->adjacency_matrix[azadpur_yellow][azadpur_pink] = 5;
    }
    int rajourigarden_blue = find_station_index(network, "rajourigarden");
    int rajourigarden_pink = find_station_index(network, "rajourigarden");
    if (rajourigarden_pink != -1 && rajourigarden_blue != -1) {
        network->adjacency_matrix[rajourigarden_pink][rajourigarden_blue] = 5;
        network->adjacency_matrix[rajourigarden_blue][rajourigarden_pink] = 5;
    }
    int sukhdevvihar_magenta = find_station_index(network, "sukhdevvihar");
    int sukhdevvihar_pink = find_station_index(network, "sukhdevvihar");
    if (sukhdevvihar_pink != -1 && sukhdevvihar_magenta != -1) {
        network->adjacency_matrix[sukhdevvihar_pink][sukhdevvihar_magenta] = 5;
        network->adjacency_matrix[sukhdevvihar_magenta][sukhdevvihar_pink] = 5;
    }
    int welcome_red = find_station_index(network, "welcome");
    int welcome_pink = find_station_index(network, "welcome");
    if (welcome_pink != -1 && welcome_red != -1) {
        network->adjacency_matrix[welcome_pink][welcome_red] = 5;
        network->adjacency_matrix[welcome_red][welcome_pink] = 5;
    }
    //Add other interchanges here.
    int dwarka_grey = find_station_index(network, "dwarka");
    int dwarkasec21_orange = find_station_index(network,"dwarkasec21");
    if(dwarka_grey != -1 && dwarkasec21_orange != -1){
        network->adjacency_matrix[dwarka_grey][dwarkasec21_orange] = 5;
        network->adjacency_matrix[dwarkasec21_orange][dwarka_grey]= 5;
    }

    return network;
}

// Dijkstra's Algorithm for Shortest Path
void dijkstra_shortest_path(MetroNetwork* network, int start_idx, int end_idx) {
    int dist[MAX_STATIONS];
    int prev[MAX_STATIONS];
    bool visited[MAX_STATIONS];
    int transfers[MAX_STATIONS];

    // Initialize
    for (int i = 0; i < network->station_count; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = false;
        transfers[i] = 0;
    }

    dist[start_idx] = 0;

    // Find shortest path
    for (int count = 0; count < network->station_count - 1; count++) {
        // Find minimum distance vertex
        int u = -1;
        int min_dist = INF;
        for (int v = 0; v < network->station_count; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                min_dist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        // Update adjacent vertices
        for (int v = 0; v < network->station_count; v++) {
            if (!visited[v] &&
                network->adjacency_matrix[u][v] != INF) {
                // Check if transfer is needed
                bool is_transfer = strcmp(network->stations[u].line, network->stations[v].line) != 0;

                int new_dist = dist[u] + network->adjacency_matrix[u][v];
                int new_transfers = transfers[u] + (is_transfer ? 1 : 0);

                if (new_dist < dist[v] ||
                    (new_dist == dist[v] && new_transfers < transfers[v])) {
                    dist[v] = new_dist;
                    prev[v] = u;
                    transfers[v] = new_transfers;
                }
            }
        }
    }

    // Reconstruct path
    if (dist[end_idx] == INF) {
        printf("No path exists between these stations.\n");
        return;
    }

    // Backtrack path
    int path[MAX_STATIONS];
    int path_length = 0;
    for (int at = end_idx; at != -1; at = prev[at]) {
        path[path_length++] = at;
    }

    // Print path in correct order
    printf("Shortest Route:\n");
    int interchanges = 0;
    char current_line[20] = "";
    for (int i = path_length - 1; i >= 0; i--) {
        // Check for line change
        if (strcmp(current_line, network->stations[path[i]].line) != 0 && current_line[0] != '\0') {
            printf("(Interchange to %s Line)\n", network->stations[path[i]].line);
            interchanges++;
        }

        printf("%s (%s Line)", network->stations[path[i]].name, network->stations[path[i]].line);
        strcpy(current_line, network->stations[path[i]].line);

        if (i > 0) printf(" -> ");
    }
    printf("\n");

    printf("Total Stations: %d\n", path_length);
    printf("Total Interchanges: %d\n", interchanges);
    printf("Estimated Travel Time: %d minutes\n", dist[end_idx]);
}

int main() {
    MetroNetwork* network = create_metro_network();
    char start[50], dest[50];

    while (1) {
        printf("\n* Delhi Metro Route Finder  *\n");
        printf("1. Find Shortest Route\n");
        printf("2. View All Stations\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number (1, 2, or 3).\n");
            continue;
        }
        getchar(); // Consume newline

        switch (choice) {
            case 1:
                printf("Enter Source Station: ");
                fgets(start, sizeof(start), stdin);
                start[strcspn(start, "\n")] = 0;

                printf("Enter Destination Station: ");
                fgets(dest, sizeof(dest), stdin);
                dest[strcspn(dest, "\n")] = 0;

                // Normalize inputs
                char* norm_start = normalize_input(start);
                char* norm_dest = normalize_input(dest);

                // Debug: Print normalized inputs
                printf("Normalized Source: %s\n", norm_start);
                printf("Normalized Destination: %s\n", norm_dest);

                // Find station indices
                int start_idx = find_station_index(network, norm_start);
                int end_idx = find_station_index(network, norm_dest);

                if (start_idx == -1 || end_idx == -1) {
                    printf("Error: One or both stations not found.\n");
                    printf("Available stations:\n");
                    for (int i = 0; i < network->station_count; i++) {
                        printf("%s (%s Line)\n", network->stations[i].name, network->stations[i].line);
                    }
                } else {
                    dijkstra_shortest_path(network, start_idx, end_idx);
                }

                free(norm_start);
                free(norm_dest);
                break;

            case 2:
                printf("Stations in Network:\n");
                for (int i = 0; i < network->station_count; i++) {
                    printf("%s (%s Line)\n", network->stations[i].name, network->stations[i].line);
                }
                break;

            case 3:
                free(network);
                printf("Thank you for using Delhi Metro Route Finder!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

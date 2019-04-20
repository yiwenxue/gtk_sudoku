/*************************************************************************
    > File Name: main.c
    > Author: Yiwen Xue
    > Mail: 15225434259xue@gmail.com 
    > Created Time: Sat 20 Apr 2019 01:58:59 PM IDT
*************************************************************************/

#include <stdio.h>
#include <malloc.h>
#include "sudoku.h"
#include <gtk/gtk.h>

int WIDTH = 600;
int HEIGHT = 600;
int puzzle[9][9]; 


static void destroy(GtkWidget *window,
        gpointer data){
    gtk_main_quit();
}

static gboolean delete_event(GtkWidget *window,
       GdkEvent *event,
       gpointer data){
    return false;
}

static gboolean print_hello(GtkWidget *window,
        gpointer data){
    printf("Hello World\n");
}

static gboolean load_file(GtkButton *button,
        gpointer *data){
    FILE* file;
    file = fopen("data","r");
    for(int i=0;i<9;i++){
        fscanf(file,"%d %d %d %d %d %d %d %d %d\n",
                &puzzle[i][0],&puzzle[i][1],&puzzle[i][2],
                &puzzle[i][3],&puzzle[i][4],&puzzle[i][5],
                &puzzle[i][6],&puzzle[i][7],&puzzle[i][8]);
    }
    /* print_puzzle((int*)puzzle); */
    fclose(file);
    char name[255];
    /* gtk_label_set_text((GtkLabel* )data,"H"); */

    for(int j=0;j<9;j++){
        for(int i=0;i<9;i++){
            sprintf(name,"%d",puzzle[j][i]);
            gtk_label_set_text((GtkLabel *)(data[j*9+i]),name);
        }
    }
}

void update_layout(GtkWidget *window,
        gpointer data){
}

static gboolean solve_sudoku(GtkWidget *window,
        gpointer *data){

    if(!solveSudoku(puzzle,0))
        printf("This can't be solved.\n");
    else
        printf("I solved this sudoku, my lord.\n");
    
    char name[255];
    for(int j=0;j<9;j++){
        for(int i=0;i<9;i++){
            sprintf(name,"%d",puzzle[j][i]);
            gtk_label_set_text((GtkLabel *)(data[j*9+i]),name);
        }
    }
}

typedef struct{
    int i;
    GtkWidget *target;
} Data; 

int main(int argc,char **argv){
    
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            puzzle[i][j] = 0;
        }
    }

    GtkWidget *window, *grid;
    GtkWidget *child_grid[9];
    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Sudoku");
    gtk_container_set_border_width(GTK_CONTAINER(window),10);
    gtk_widget_set_size_request(window,WIDTH,HEIGHT);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);

    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(destroy),NULL);
    g_signal_connect(G_OBJECT(window), "delete_event",G_CALLBACK(delete_event),NULL);

    /* gtk_widget_show(window); */
    grid = gtk_grid_new();

    gtk_grid_set_row_homogeneous(GTK_GRID(grid),TRUE);
    gtk_grid_set_row_spacing(GTK_GRID(grid),3);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid),TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid),3);

    gtk_container_add (GTK_CONTAINER (window), grid);


    GtkWidget *label[81];
    GtkWidget *frame[9];

    GdkRGBA gray;
    gray.red = 0.8;
    gray.green = 0.8;
    gray.blue = 0.8;

    char name[255];

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            child_grid[i*3+j] = gtk_grid_new();
            gtk_grid_set_row_homogeneous(GTK_GRID(child_grid[i*3+j]),TRUE);
            gtk_grid_set_row_spacing(GTK_GRID(child_grid[i*3+j]),2);
            gtk_grid_set_column_homogeneous(GTK_GRID(child_grid[i*3+j]),TRUE);
            gtk_grid_set_column_spacing(GTK_GRID(child_grid[i*3+j]),2);
            frame[i*3+j] = gtk_frame_new(NULL);
            
            gtk_container_add(GTK_CONTAINER(frame[j+i*3]),child_grid[i*3+j]);
            gtk_grid_attach(GTK_GRID(grid),frame[i*3+j],j*3,i*3,3,3);
        }
    }

    int x,y;
    for(int j=0;j<9;j++){
        for(int i=0;i<9;i++){
            sprintf(name,"%d",puzzle[j][i]);
            label[j*9+i] = gtk_label_new(name);
            /* g_signal_connect_swapped(G_OBJECT(label[j*9+i]), "clicked", */
            /*         G_CALLBACK(print_hello),(gpointer)label[j*9+i]); */
            x = i/3;
            y = j/3;
            gtk_grid_attach(GTK_GRID (child_grid[y*3+x]), label[j*9+i], i-x*3, j-y*3, 1, 1);
        }
    }

    /* label = gtk_label_new("Hello"); */
    /* gtk_grid_attach(GTK_GRID (grid), label, 0, 0, 9, 9); */

    GtkWidget *button,*button1,*button2;

    button = gtk_button_new_with_label("New");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(load_file),label);
    gtk_grid_attach(GTK_GRID(grid),button,0,10,3,1);

    button1 = gtk_button_new_with_label("Solve");
    g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(solve_sudoku),label);
    gtk_grid_attach(GTK_GRID(grid),button1,3,10,3,1);

    button2 = gtk_button_new_with_label("Quit");
    g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(destroy),button2);
    gtk_grid_attach(GTK_GRID(grid),button2,6,10,3,1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}


#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

static GtkWidget *input_label;
static GtkWidget *output_label;
static GtkWidget *amount_label;
static GtkWidget *amount;
static GtkWidget *currency1;
static GtkWidget *currency2;
static GtkWidget *result_label;
static GtkWidget *result;
static GtkWidget *space_label1;
static GtkWidget *space_label2;

//Converts currency name to lowercase
char* toLower(char* str)
{
    size_t len = strlen(str);
    char *lower = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i)
    {
        lower[i] = tolower((unsigned char)str[i]);
    }
    return lower;
}

//Calculates amount when convert button is clicked
void do_calculate(GtkWidget *calculate, gpointer data) {
    //Receives input through GUI Interface
    char* cur1 = (char *)gtk_entry_get_text(GTK_ENTRY(currency1));
    char* cur2 = (char *)gtk_entry_get_text(GTK_ENTRY(currency2));
    float amt  = atof((char*)gtk_entry_get_text(GTK_ENTRY(amount)));
    printf("amount = %f\n", amt);

    float currency_values[25] = {1.0, 73.36, 88.97, 0.67, 19.97, 103.16, 1.02, 11.47, 244.76, 0.000023,0.37,53.99,58.93,0.0052,0.064,8.49,5.01,81.35,51.64,54.49,3332225,225355,29262.48,146.33,
                                22.30   };
    char currency_names[25][100] = {"INR", "USD", "EUR", "JPY", "AED", "GBP", "RUB", "CNY", "KWD", "VEB","LKR","AUD","CAD","IDR","KRW","SEK","ZAR","CHF","NZD","SGD","BTC","ETH","BNB","ADA","DOGE"};

    float final_amt = amt;
    //initialized to -1 to check later if inputs are valid
    float value1 = -1;
    float value2 = -1;

    for (int i = 0; i < 25; i++)
    {
        //checks if input currency names are valid
        if (strcmp(cur1, currency_names[i]) == 0 || strcmp(cur1, toLower(currency_names[i])) == 0)
        {
            value1 = currency_values[i];
        }

        if (strcmp(cur2, currency_names[i]) == 0 || strcmp(cur2, toLower(currency_names[i])) == 0)
        {
            value2 = currency_values[i];
        }
    }

    char buffer[32];
    //data validation
    if (value1 == -1 || value2 == -1)
    snprintf(buffer, sizeof(buffer), "INVALID INPUT");
    //prints converted amount in GUI Window
    else
    snprintf(buffer, sizeof(buffer), "  %.2f    ", amt * value1 / value2);

    gtk_label_set_text(GTK_LABEL(result), buffer);
}


// gcc 007_gtk.c -o 007_gtk `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
int main(int argc, char **argv)
{
    printf("    ENTER INR for RUPEES \n");
    printf("    ENTER USD for US DOLLARS\n");
    printf("    ENTER EUR for EUROS\n");
    printf("    ENTER JYP for YEN\n");
    printf("    ENTER AED for DIRHAM\n");
    printf("    ENTER GBD for POUND \n");
    printf("    ENTER RUB for RUBLE\n");
    printf("    ENTER CNY for YUAN\n");
    printf("    ENTER KWD for KUWAITI DINAR\n");
    printf("    ENTER VEB for VENEZUALAN BOLIVAR\n");
    printf("    ENTER LKR for SRILANKAN RUPEES \n");
    printf("    ENTER AUD for AUSTRALIAN DOLLAR \n");
    printf("    ENTER CAD for CANADIAN DOLLAR \n");
    printf("    ENTER IDR for INDONESIAN RUPIAHS \n");
    printf("    ENTER KRW for SOUTH KOREAN WON \n");
    printf("    ENTER SEK for SWEDISH KRONA \n");
    printf("    ENTER ZAR for SOUTH AFRICAN RAND\n");
    printf("    ENTER CHF for SWISS FRANC \n");
    printf("    ENTER NZD for NEW ZEALAND DOLLAR \n");
    printf("    ENTER SGD for SINGAPORE DOLLAR \n\n");
    printf("    CRYPTOCURRENCIES:\n");
    printf("    ENTER BTC for BITCOIN \n");
    printf("    ENTER ETH for ETHEREUM \n");
    printf("    ENTER BNB for BINANCE COIN \n");
    printf("    ENTER ADA for CARDANO \n");
    printf("    ENTER DOFE for DOGECOIN \n");

    //GUI Part

    GtkWidget *window, *grid, *calculate;
    gtk_init(&argc, &argv);

    //creates a window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Currency Converter");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    //adds grid container to window
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    //adds labels and entries to the window

    amount_label = gtk_label_new("  Amount  ");
    gtk_grid_attach(GTK_GRID(grid), amount_label, 0, 0, 1, 1);

    amount = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), amount, 1, 0, 1, 1);

    space_label1 = gtk_label_new("          ");
    gtk_grid_attach(GTK_GRID(grid), space_label1, 2, 0, 1, 1);

    result_label = gtk_label_new("  Amount  ");
    gtk_grid_attach(GTK_GRID(grid), result_label, 3, 0, 1, 1);

    result = gtk_label_new("           ");
    gtk_grid_attach(GTK_GRID(grid), result, 4, 0, 1, 1);

    input_label = gtk_label_new("   Currency 1  ");
    gtk_grid_attach(GTK_GRID(grid), input_label, 0, 1, 1, 1);

    currency1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), currency1, 1, 1, 1, 1);

    space_label2 = gtk_label_new("           ");
    gtk_grid_attach(GTK_GRID(grid), space_label2, 2, 0, 1, 1);

    output_label = gtk_label_new("  Currency 2  ");
    gtk_grid_attach(GTK_GRID(grid), output_label, 3, 1, 1, 1);

    currency2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), currency2, 4, 1, 1, 1);

    //adds convert button to window, when clicked it calls do_calculate function
    calculate = gtk_button_new_with_label(" Convert ");
    g_signal_connect(calculate, "clicked", G_CALLBACK(do_calculate), NULL);
    gtk_grid_attach(GTK_GRID(grid), calculate, 2, 3, 1, 1);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

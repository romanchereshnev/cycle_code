#include "Word.h"
#include "Tools.h"
#include <cstdio>
#include <cstring>
#include <gtk/gtk.h> /* подключаем GTK+ */

static gint delete_event_cb(GtkWidget *w, GdkEventAny *e, gpointer data);
static void button_click_ent(GtkWidget *w, gpointer data);
static void button_click_dec(GtkWidget *w, gpointer data);
bool check_poly(char * s);
int find_k(int n);

const int MAX = 9;
const char * irred_polyn[MAX] =
{
		"1", "111", "1011", "10011", "100101",
		"1000011", "10001001", "100011101", "1000010001"
};

struct Data
{
	int err;
	Word * px;
	Word * word;
	Word * contr_mtrx;
	char tmp[200000];

	GtkWidget * lbl_bin_pol;
	GtkWidget * lbl_bin_cod_word;
	GtkWidget *lbl_mtrx;
	GtkWidget *lbl_cod;
	GtkWidget * lbl_bin_res_word;
	GtkWidget * lbl_bin_dec_word ;
	GtkWidget *lbl_dec;
	GtkWidget *ent_poly;
	GtkWidget *but_spin;
};

int main(int argc, char ** argv)
{
	using namespace std;

	Data data;

	data.px = NULL;
	data.word = NULL;
	data.contr_mtrx = NULL;

	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);  // Общее окно
	GtkWidget *hbox = gtk_hbox_new(true,0);	// Область в которой будут два фрейма

	GtkWidget *frame_cod = gtk_frame_new ("Кодирование");  // Область для кодировая
	GtkWidget *frame_dec = gtk_frame_new ("Декодирование"); // Область для декодирования

	GtkWidget *table_cod = gtk_table_new(10,10, false); // Таблица для виджетов кодирования
	GtkWidget *table_dec = gtk_table_new(10,10, false); // Таблица для виджетов декодирования

	//Виджеты для кодировния

	data.ent_poly = gtk_entry_new(); // Область ввода полинома.

	GtkWidget * lbl_word_to_send = gtk_label_new("Слово для передачи "); 	// Надпись "Слово для передачи"
	GtkWidget * lbl_polynorm = gtk_label_new("Порождающий полином ");    	// Надпись "Порождающий полином"
	data.lbl_bin_pol = gtk_label_new("Пока не выбран "); 		// Сам полином
	GtkWidget * lbl_cod_word = gtk_label_new("Слово для передачи ");		// Надпись "Закодированиое слово"
	data.lbl_bin_cod_word = gtk_label_new("Пока не выбранно ");    // Само закодированное слово

	GtkWidget *but_ent = gtk_button_new_with_label("Ввести"); 	//Копка для ввода слова
	

	GtkWidget *frm_mtrx = gtk_frame_new ("Остатки от деления"); 	//область для остатков деления
	GtkWidget * scrolled_mtrx = gtk_scrolled_window_new (NULL, NULL);

	GtkWidget *frm_cod = gtk_frame_new ("Кодирование"); //область для кодирования полинома
	GtkWidget * scrolled_cod = gtk_scrolled_window_new (NULL, NULL);

	data.lbl_mtrx = gtk_label_new("\n"); 	//текст для нахождения матрицы
	data.lbl_cod = gtk_label_new("\n"); //текст для кодирования

	//Виджеты для декодировния
	GtkAdjustment * adj = (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, 20.0, 1.0, 0.0, 0.0 );
	data.but_spin = gtk_spin_button_new(adj, 1.0, 0); //Кнопка карусель, для выбора номера разряда
	GtkWidget *but_dec  = gtk_button_new_with_label("Декодировать слово"); // Кнопка декодировать

	GtkWidget * lbl_err  = gtk_label_new("Сделать ошибку в разряде номер");
	GtkWidget * lbl_res_word  = gtk_label_new("Полученное слово");		// Надпись "Полученное слово"
	data.lbl_bin_res_word  = gtk_label_new("\n");    // Само полученное слово
	GtkWidget * lbl_dec_word  = gtk_label_new("Декодированное слово");		// Надпись "Декодированное слово"
	data.lbl_bin_dec_word = gtk_label_new("\n");    // Само декодированное слово

	GtkWidget *frm_dec = gtk_frame_new ("Декодирование"); ; 	//область для декодирования
	GtkWidget * scrolled_dec = gtk_scrolled_window_new (NULL, NULL);
	data.lbl_dec = gtk_label_new ("\n");	//текст для декодирования

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_mtrx),  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_cod),  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_dec),  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	gtk_container_add(GTK_CONTAINER(window), hbox);

	gtk_box_pack_start( GTK_BOX (hbox), frame_cod, true, true, 0);
	gtk_box_pack_start( GTK_BOX (hbox), frame_dec, true, true, 0);

	gtk_container_add(GTK_CONTAINER(frame_cod), table_cod);
	gtk_container_add(GTK_CONTAINER(frame_dec), table_dec);

	gtk_table_attach(GTK_TABLE (table_cod), lbl_word_to_send, 0, 3, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);
	gtk_table_attach(GTK_TABLE (table_cod), data.ent_poly, 5, 8, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);
	gtk_table_attach(GTK_TABLE (table_cod), but_ent, 8, 10, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);
	gtk_table_attach(GTK_TABLE (table_cod), lbl_polynorm, 0, 3, 1, 2, GTK_SHRINK, GTK_SHRINK, 0, 0);
	gtk_table_attach(GTK_TABLE (table_cod), data.lbl_bin_pol, 5, 10, 1, 2, GTK_SHRINK, GTK_SHRINK, 0, 0);

	gtk_table_attach_defaults (GTK_TABLE (table_cod), frm_mtrx, 0, 5, 2, 9);
	gtk_container_add(GTK_CONTAINER(frm_mtrx),scrolled_mtrx);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW (scrolled_mtrx), data.lbl_mtrx);

	gtk_table_attach_defaults (GTK_TABLE (table_cod), frm_cod, 5, 9, 2, 9);
	gtk_container_add(GTK_CONTAINER(frm_cod), scrolled_cod);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW (scrolled_cod), data.lbl_cod);

	gtk_table_attach(GTK_TABLE (table_cod), lbl_cod_word, 0, 3, 9, 10, GTK_SHRINK, GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE (table_cod), data.lbl_bin_cod_word, 5, 10, 9, 10, GTK_SHRINK, GTK_SHRINK, 5, 5);

	gtk_table_attach (GTK_TABLE (table_dec), lbl_err, 0, 2, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);
	gtk_table_attach(GTK_TABLE (table_dec), data.but_spin, 2, 3, 0, 1, GTK_SHRINK, GTK_SHRINK, 0, 0);

	gtk_table_attach(GTK_TABLE (table_dec), lbl_res_word, 0, 1, 4, 5, GTK_SHRINK, GTK_SHRINK, 0, 0);
	gtk_table_attach(GTK_TABLE (table_dec), data.lbl_bin_res_word, 2, 4, 4, 5, GTK_SHRINK, GTK_SHRINK, 0, 0);

	gtk_table_attach(GTK_TABLE (table_dec), but_dec, 0, 4, 5, 6, GTK_SHRINK, GTK_SHRINK, 0, 0);

	gtk_table_attach_defaults (GTK_TABLE (table_dec), frm_dec, 0, 10, 6, 8);
	gtk_container_add(GTK_CONTAINER(frm_dec), scrolled_dec);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW (scrolled_dec), data.lbl_dec);

	gtk_table_attach(GTK_TABLE (table_dec), lbl_dec_word, 0, 4, 9, 10, GTK_SHRINK, GTK_SHRINK, 5, 5);
	gtk_table_attach(GTK_TABLE (table_dec), data.lbl_bin_dec_word, 5, 10, 9, 10, GTK_SHRINK, GTK_SHRINK, 5, 5);

	gtk_window_set_title(GTK_WINDOW(window), "Циклический код");

	gtk_signal_connect(GTK_OBJECT(window), "delete_event",GTK_SIGNAL_FUNC(delete_event_cb), NULL);
	gtk_signal_connect(GTK_OBJECT(but_ent), "clicked",GTK_SIGNAL_FUNC(button_click_ent), &data);
	gtk_signal_connect(GTK_OBJECT(but_dec), "clicked",GTK_SIGNAL_FUNC(button_click_dec), &data);

	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
	gtk_widget_show_all(window);

	gtk_main();
}

static gint delete_event_cb(GtkWidget *window, GdkEventAny *e,  gpointer data)
{
  gtk_main_quit();
  return false;
}

void button_click_ent(GtkWidget *w, gpointer data)
{
	Data * tmp = (Data*)data;
	int k;
	strcpy(tmp->tmp, gtk_entry_get_text( (GtkEntry*)tmp->ent_poly ));
	if(!check_poly(tmp->tmp) )
	{
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_mtrx), "Введен неверный полином!" );
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_bin_pol), "" );
	}
	else
	{
		delete tmp->px;
		delete tmp->word;
		delete [] tmp->contr_mtrx;

		tmp->word = new Word(tmp->tmp);
		tmp->px = new Word(irred_polyn[find_k(strlen(tmp->tmp)) - 1]);
		tmp->word->leftShift(tmp->px->max());
		k = find_k(strlen(tmp->tmp)) - 1;
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_bin_pol), irred_polyn[k] );

		tmp->contr_mtrx = control_mtrx(strlen(tmp->tmp) + strlen(irred_polyn[k]), *(tmp->px), tmp->tmp);
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_mtrx), tmp->tmp );
		word_codding(*tmp->word, *tmp->px, tmp->tmp);
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_cod), tmp->tmp );

		gtk_label_set_text( (GtkLabel*)(tmp->lbl_bin_cod_word), tmp->word->to_char() );

		GtkAdjustment * adj =  (GtkAdjustment *)gtk_adjustment_new(1.0, 1.0, tmp->word->len(), 1.0, 0.0, 0.0 );
		gtk_spin_button_configure( (GtkSpinButton*)tmp->but_spin, adj, 0.0 , 0.0);
	}

}

void button_click_dec(GtkWidget *wind, gpointer data)
{
	Data * tmp = (Data *) data;
	if(tmp->word)
	{
		int err = gtk_spin_button_get_value_as_int( (GtkSpinButton *)(tmp->but_spin));
		Word w =*tmp->word;
		w[err - 1] = !w[err - 1];
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_bin_res_word), w.to_char() );

		error_correct(tmp->contr_mtrx, w, *tmp->px, tmp->tmp);
		gtk_label_set_text( (GtkLabel*)(tmp->lbl_dec), tmp->tmp);
		gtk_label_set_text((GtkLabel*)(tmp->lbl_bin_dec_word), w.to_char());

	}
}




#include <gtk/gtk.h>
#include <ctype.h>
#include <stdio.h>
void ButtonClick(GtkWidget *button, gpointer data);
gchar *Result(const gchar *expression);
//숫자버튼 10개, 계산 버튼 5개, 초기화 버튼
GtkWidget *buttons[16];
const char *labels[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", 
                        "+", "-", "%", "X", "=", "C"};
int main(int argc, char *argv[]){
    GtkWidget *window;
    GtkWidget *vbox;       
    GtkWidget *hbox;   
    GtkWidget *textview;
    GtkTextBuffer *textbuffer;
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Simple Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    //vBox 생성
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    //텍스트 뷰 설정
    textview = gtk_text_view_new();
    gtk_widget_set_size_request(textview, 400, 40);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD_CHAR);
    textbuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_box_pack_start(GTK_BOX(vbox), textview, FALSE, FALSE, 0); //vbox에 추가
    //버튼 설정
    for (int i = 0; i < 16; i++) {
        //hbox 생성
        if (i % 4 == 0) {
            hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);
        }

        buttons[i] = gtk_button_new_with_label(labels[i]);
        g_signal_connect(buttons[i], "clicked", G_CALLBACK(ButtonClick), textbuffer);
        gtk_box_pack_start(GTK_BOX(hbox), buttons[i], TRUE, TRUE, 0); //hbox에 추가
    }
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
void ButtonClick(GtkWidget *button, gpointer data){
    const gchar *button_label = gtk_button_get_label(GTK_BUTTON(button));
    GtkTextBuffer *text_buffer = GTK_TEXT_BUFFER(data);
    GtkTextIter start, end;
    if (g_strcmp0(button_label, "=") == 0) {
        gtk_text_buffer_get_start_iter(text_buffer, &start);
        gtk_text_buffer_get_end_iter(text_buffer, &end);
        gchar *curtext = gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
        //계산하기
        gchar *result = Result(curtext);
        //결과 출력
        gtk_text_buffer_set_text(text_buffer, result, -1);
        g_free(curtext);
        return;
    }
    //초기화
    if (g_strcmp0(button_label, "C") == 0) {
        gtk_text_buffer_set_text(text_buffer, "", -1);
        return;
    }
    //TextView 끝에 문자 추가
    gtk_text_buffer_get_end_iter(text_buffer, &end);
    gtk_text_buffer_insert(text_buffer, &end, button_label, -1);
}
//계산 함수
gchar *Result(const gchar *expression){
    double result = 0.0;
    char operator = 0;
    double current_number = 0.0;
    const gchar *p = expression;
    //수식 읽기
    while (*p != '\0') {
        //숫자 읽기
        if (isdigit(*p) || *p == '.') {
            char num_buf[32] = {0};  // 숫자를 저장할 버퍼
            int i = 0;
            while (isdigit(*p) || *p == '.') {
                num_buf[i++] = *p++;
            }
            current_number = atof(num_buf);
            // 연산 처리
            if (operator == 0) {
                result = current_number;  // 첫 숫자
            } 
            else {
                switch (operator) {
                    case '+': result += current_number; break;
                    case '-': result -= current_number; break;
                    case 'X': result *= current_number; break;
                    case '%': 
                        if (current_number != 0) {
                            result /= current_number; 
                        } 
                        else {
                            return g_strdup("Error: Division by zero");
                        }
                        break;
                }
            }
        }
        //연산자 읽기
        if (*p == '+' || *p == '-' || *p == 'X' || *p == '%') {
            operator = *p;
            p++;
        } else if (!isdigit(*p) && *p != '\0') {
            // 잘못된 문자 처리
            return g_strdup("Wrong Operator");
        }
    }
    // 결과 문자열로 변환
    gchar *result_str = g_strdup_printf("%.2f", result);
    return result_str;
}
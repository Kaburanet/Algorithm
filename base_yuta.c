//最低限の入出力と、計算、時間測定のみを行うプログラムです。O(PNK)
//このプログラムはgcc -O2 base_yuta.cでO2指定ができて、MODEL2で約3倍の実行速度になる。
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1001//Aさん含めると1001人
#define M 10000
#define P 50000

int main(void){

    int *l,*s;
    l = (int *)malloc((P+1) * sizeof(int));
    s = (int *)malloc((P+1) * sizeof(int));
    //時間計測
    long start_cpu_time = clock();
    
    //01ファイルの読み込み-------------------------------------
    FILE *file1;
    char **strings = malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        strings[i] = malloc((M + 1) * sizeof(char));
    }

    file1 = fopen("MODEL2_rev/data9", "r");
    if (file1 == NULL) {
        perror("ファイルのオープンに失敗しました");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(file1, "%10000s", strings[i]) != 1) {
            fprintf(stderr, "ファイルからの読み取りエラー\n");
            break;
        }
    }

    fclose(file1);

    // 区間ファイルの読み込み & 実際の計算---------------------------------------
    FILE *file2;
    int L, S;

    file2 = fopen("MODEL2_rev/range9", "r");
    if (file2 == NULL) {
        perror("ファイルのオープンに失敗しました");
        return 1;
    }
    char buffer[256];
    char *a = fgets(buffer,256,file2);
    //printf("%s",buffer);//MODEL1の文字列を例外にできているかのチェック　OK
    int q_num = 0;
    while (fscanf(file2, "%d,%d", &L, &S) == 2) {
        l[q_num] = L;
        s[q_num] = S;
        q_num++;
    }
    //printf("%d,%d\n",l[0],s[0]);//読込チェック OK

    fclose(file2);

    

    //計算===========================================
    int *ans;
    ans = (int *)malloc(q_num * sizeof(int));
    for(int i=0;i<q_num;i++){
        ans[i] = 0;
        
        for(int j=1;j<N;j++){
            int key = 1;
            for(int k=l[i];k<l[i]+s[i];k++){//l[i]>=0なのでこのままで大丈夫
                if(strings[0][k] != strings[j][k]){
                    key = 0;
                    break;
                }
            }
            if(key==1){
                ans[i]++;
            }
        }
    }


    for (int i = 0; i < N; i++) {
        free(strings[i]);
    }
    free(strings);


     // ファイルを開く
    FILE *file;
    file = fopen("ans0.txt", "w");
    if (file == NULL) {
        perror("ファイルのオープンに失敗しました");
        return 1;
    }

    // 配列の要素をファイルに書き込む
    for (int i = 0; i < q_num; i++) {
        fprintf(file, "%d, %d, %d\n", l[i], s[i], ans[i]);
    }

    // ファイルを閉じる
    fclose(file);


    //時間計測と計算------------------------------------------
    long end_cpu_time = clock();
    long cpu_time = end_cpu_time - start_cpu_time;
    double sec = (double)cpu_time / CLOCKS_PER_SEC;
    printf("succeeded!\n Time: %f秒\n", sec);
    return 0;
}

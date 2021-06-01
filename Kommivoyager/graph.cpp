#include "graph.h"
#include "newedgeform.h"
#include "newmatrixform.h"
#include "delvertform.h"
#include "deledgeform.h"
#include "ui_graph.h"
#include <cmath>
#include <QTextStream>

QTextStream cout(stdout);
QTextStream cin(stdin);

int     radiusA = 20,
        radiusB = 170;


QString Graph::tsalesman()
{
    int n;
    int* res;
    int** help;
    int*** mat;

    n = kol;

    help = new int* [n];

    res = new int[n];

    mat = new int** [n];

    for (int i = 0; i <= n; i++)
    {
        help[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        mat[i] = new int* [n];
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0) {
                mat[i][j] = nullptr;
                continue;
            }
            mat[i][j] = new int(matrix[i][j]);
        }
    }

    for (int l = 0; l < n; l++)
    {
        for (int i = 0; i < n; i++)
        {
            int min = 1000000;
            for (int j = 0; j < n; j++)
                if (mat[i][j] && min > * mat[i][j])
                    min = *mat[i][j];
            for (int j = 0; j < n; j++)
                if (mat[i][j])
                    *mat[i][j] -= min;
        }
        for (int j = 0; j < n; j++)
        {
            int min = 1000000;
            for (int i = 0; i < n; i++)
                if (mat[i][j] && min > * mat[i][j])
                    min = *mat[i][j];
            for (int i = 0; i < n; i++)
                if (mat[i][j])
                    *mat[i][j] -= min;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                help[i][j] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (mat[i][j] && !*mat[i][j])
                {
                    int hmin = 1000000;
                    int vmin = 1000000;

                    for (int l = 0; l < n; l++)
                        if (l != i && mat[l][j] && hmin > * mat[l][j])
                            hmin = *mat[l][j];

                    for (int l = 0; l < n; l++)
                        if (l != j && mat[i][l] && vmin > * mat[i][l])
                            vmin = *mat[i][l];

                    help[i][j] = hmin + vmin;
                }
            }

        int mcost = 0, mi = 0, mj = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] && mcost < help[i][j])
                {
                    mcost = help[i][j];
                    mi = i;
                    mj = j;
                }
        res[mi] = mj;

        for (int i = 0; i < n; i++)
            mat[i][mj] = nullptr;

        for (int i = 0; i < n; i++)
            mat[mi][i] = nullptr;

        mat[mj][mi] = nullptr;
    }

    int s = 0;
    QString tmp = "";

    tmp += QString("\nОтрезки путей: ");
    for (int i = 0, j = 0; i < n; i++)
    {
        j = res[i];
        tmp += QString::number(i + 1) + QString("->") + QString::number(j + 1) + QString("  ");
        s += matrix[i][j];
    }
    cout << "\n";
    tmp += QString("\nКратчайший путь: ");
    int temp = 0;
    for (int l = 0; l < n;)
    {
        for (int i = 0, j = 0; i < n; i++)
        {
            if (temp == 0 || i + 1 == temp)
            {
                if (temp == 0) tmp += QString::number(i + 1);
                j = res[i];
                temp = j + 1;
                if (temp > 0)	tmp += QString(" -> ") + QString::number(temp);
                l++;
            }
        }
    }
    tmp += QString("\nРасстояние: ") + QString::number(s);
    return tmp;
}

int Graph::GetWeight(const int vertex1, const int vertex2)
{
    if (vertex1 >= 0 && vertex1 < matrix.size() && vertex2 >=0 && vertex2 < matrix.size())
        return matrix[vertex1][vertex2];
    else
        return 0;
}

void Graph::DrawLines(QGraphicsScene* scene)
{
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (GetWeight(i, j) > 0){
                int     vertex1_x = centerX + cos(iter * i) * radiusB,
                        vertex1_y = centerY - sin(iter * i) * radiusB,
                        vertex2_x = centerX + cos(iter * j) * radiusB,
                        vertex2_y = centerY - sin(iter * j) * radiusB;
                QGraphicsItem *line = scene->addLine(vertex1_x, vertex1_y, vertex2_x, vertex2_y);
                scene->addItem(line);
                QGraphicsTextItem *number = scene->addText(QString::number(GetWeight(i, j)), QFont("Times"));                
                number->setPos((vertex2_x + vertex1_x) / 2, (vertex2_y + vertex1_y) / 2);
            }
        }
    }
}

void Graph::DrawNodes(QGraphicsScene* scene)
{
    int     centerX= scene->width() / 2,
            centerY = scene->height() / 2;
    double iter = 2 * 3.1415 / matrix.size();
    for (int i = 0; i < matrix.size(); i++){
        QGraphicsItem *node = scene->addEllipse(centerX + cos(iter * i) * radiusB - radiusA,
                                                centerY - sin(iter * i) * radiusB - radiusA, 2*radiusA, 2*radiusA,
                                                QPen(Qt::black), QBrush(Qt::yellow));
        scene->addItem(node);
        QGraphicsTextItem *number = scene->addText(QString::number(i+1), QFont("Times"));
        number->setPos(centerX + cos(iter * i) * radiusB - radiusA + 12,
                       centerY - sin(iter * i) * radiusB - radiusA + 6);
    }
}


void Graph::DrawGraph(QGraphicsScene* scene)
{
    DrawLines(scene);
    DrawNodes(scene);
}

void Graph::Draw()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 400, 400);

    ui->graphicsView->setScene(scene);
    scene->clear();
    DrawGraph(scene);
}

void Graph::Add_Vert()
{
    for (int i = 0; i < kol; i++)
    {
        matrix[i].push_back(0);
    }

    matrix.push_back({});
    kol++;
    for (int i = 0; i < kol; i++)
    {
        matrix[kol - 1].push_back(0);
    }

}

void Graph::Del_Vert(int vert)
{
    matrix.erase(matrix.begin() + vert);
    kol--;
    for (int i = 0; i < kol; i++)
    {
        matrix[i].erase(matrix[i].begin() + vert);
    }
}

void Graph::Del_Edge(int src, int trg)
{
    matrix[src - 1][trg - 1] = 0;
}

void Graph::Add_Edge(int source, int target, int weight)
{
    if (source > 0 && source <= kol && target > 0 && target <= kol && weight > 0)
    {
        matrix[source - 1][target - 1] = weight;
    } else cout << "Ошибка добавления ребра!!!";
}

void Graph::New_Matrix()
{
    int num_of_edges, source, target, weight;
    cout << "Введите количество вершин графа: "; cin >> kol;
    cout << "Введите количество ребер графа: "; cin >> num_of_edges;
    matrix.clear();
    for (int i = 0; i < kol; i++)
    {
        matrix.push_back({});
        for (int j = 0; i < kol; i++)
        {
            matrix[i].push_back(0);
        }
    }
    for (int i = 0; i < num_of_edges; ++i)
    {
        cout << "Исходная вершина: "; cin >> source;
        cout << "Конечная вершина: "; cin >> target;
        cout << "Вес ребра: "; cin >> weight;
        Add_Edge(source, target, weight);
    }
}


void Graph::New_Edge()
{
    NewEdgeForm window;
    window.setModal(true);
    window.max_kol = kol + 1;
    window.exec();
    if(window.isSaved)
    {
        int source = window.source;
        int target = window.target;
        int weight = window.weight;

        Add_Edge(source, target, weight);
        Add_Edge(target, source, weight);
    }
}

Graph::Graph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Graph)
{
    ui->setupUi(this);
    kol = 6;
    matrix = { {0, 11, 0, 0, 0, 16 },
               {11, 0, 18, 0, 23, 0 },
               {0, 18, 0, 16, 6, 0 },
               {0, 0, 16, 0, 0, 9 },
               {0, 23, 6, 0, 0, 3 },
               {16, 0, 0, 9, 3, 0 } };
    Draw();
}

Graph::~Graph()
{
    delete ui;
}

void Graph::on_b_addVert_clicked()
{
    Add_Vert();
    Draw();
}

void Graph::on_b_komi_clicked()
{
    ui->label_komi->setText(tsalesman());
}

void Graph::on_b_newMatrix_clicked()
{
    NewMatrixForm new_mat;
    new_mat.setModal(true);
    new_mat.exec();
    if (new_mat.isSaved)
    {
        kol = new_mat.verts;
        int verts_num = new_mat.edges;
        for (int i = 0; i < verts_num; i++)
        {
            New_Edge();
        }
    }
    Draw();
}

void Graph::on_b_addEdge_clicked()
{
    New_Edge();
    Draw();
}

void Graph::on_b_delVert_clicked()
{
    DelVertForm window;
    window.setModal(true);
    window.max_kol = kol + 1;
    window.exec();
    if (window.isSaved)
    {
        Del_Vert(window.kol - 1);
    }
    Draw();
}

void Graph::on_b_delEdge_clicked()
{
    DelEdgeForm window;
    window.setModal(true);
    window.max_kol = kol + 1;
    window.exec();
    if (window.isSaved)
    {
        int source = window.source;
        int target = window.target;
        Del_Edge(source, target);
        Del_Edge(target, source);
        Draw();
    }
}

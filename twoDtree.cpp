
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int, int> ul, pair<int, int> lr, RGBAPixel a)
	: upLeft(ul), lowRight(lr), avg(a), left(NULL), right(NULL)
{
}

// twoDtree destructor, given.
twoDtree::~twoDtree()
{
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree &other)
{
	copy(other);
}

// twoDtree assignment operator, given.
twoDtree &twoDtree::operator=(const twoDtree &rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG &imIn)
{

	// YOUR CODE HERE
	height = imIn.height();
	width = imIn.width();
	stats s(imIn);
	root = buildTree(s, pair<int, int>(0, 0), pair<int, int>(imIn.width() - 1, imIn.height() - 1), true);
}

twoDtree::Node *twoDtree::buildTree(stats &s, pair<int, int> ul, pair<int, int> lr, bool vert)
{

	//std::cout<<"made new node"<<std::endl;
	// YOUR CODE HERE!!
	// std::cout<<"new node created\n";
	// static int count = 0;
	// cout << count << " ";
	// count++;

	//std::cout << "ul,lr is " << ul.first << "," << ul.second << "lr is " << lr.first << " " << lr.second << std::endl;

	twoDtree::Node *res = new twoDtree::Node(ul, lr, s.getAvg(ul, lr));

	if (ul == lr)
	{
		return res;
	}

	else if (lr.second == ul.second)
	{
		vert = true;
	}

	else if (lr.first == ul.first)
	{
		vert = false;
	}
	else
	{
		vert = vert;
	}

	if (vert)
	{
		// std::cout << "enter vert" << std::endl;
		int best_x_split = ul.first;
		long running_lowest_var = 2147483642;
		for (int x = ul.first; x <= lr.first - 1; x++)
		{
			long left_score = s.getScore(ul, pair<int, int>(x, lr.second));
			long right_score = s.getScore(pair<int, int>(x + 1, ul.second), lr);
			if (left_score + right_score <= running_lowest_var)
			{
				best_x_split = x;
				// std::cout << "left score: " << left_score <<", right score:" << right_score <<std::endl;
				// std::cout << "running_lowest_var: " << running_lowest_var <<", best_x_split:" << x <<std::endl;
				running_lowest_var = left_score + right_score;
			}
		}

		res->left = buildTree(s, ul, pair<int, int>(best_x_split, lr.second), false);
		res->right = buildTree(s, pair<int, int>(best_x_split + 1, ul.second), lr, false);
	}

	else
	{
		// std::cout << "enter horizontal" << std::endl;
		int best_y_split = ul.second;
		long running_lowest_var2 = 2147483642;
		for (int y = ul.second; y <= lr.second - 1; y++)
		{
			long top_score = s.getScore(ul, pair<int, int>(lr.first, y));
			long bot_score = s.getScore(pair<int, int>(ul.first, y + 1), lr);
			if (top_score + bot_score <= running_lowest_var2)
			{
				best_y_split = y;
				// std::cout << "top_score: " << top_score <<", bot_score :" << bot_score <<std::endl;
				// std::cout << "running_lowest_var: " << running_lowest_var2 <<", best_y_split:" << y <<std::endl;
				running_lowest_var2 = top_score + bot_score;
			}
		}
		res->left = buildTree(s, ul, pair<int, int>(lr.first, best_y_split), true);
		res->right = buildTree(s, pair<int, int>(ul.first, best_y_split + 1), lr, true);
	}

	return res;
}

void twoDtree::render_helper(PNG &img, twoDtree::Node *root)
{
	if (root == NULL)
	{
		return;
	}

	if (root->left == NULL && root->right == NULL)
	{
		for (int x = root->upLeft.first; x <= root->lowRight.first; x++)
		{
			for (int y = root->upLeft.second; y <= root->lowRight.second; y++)
			{
				img.getPixel(x, y)->r = root->avg.r;
				img.getPixel(x, y)->g = root->avg.g;
				img.getPixel(x, y)->b = root->avg.b;
				img.getPixel(x, y)->a = root->avg.a;
			}
		}
	}
	render_helper(img, root->left);
	render_helper(img, root->right);
}
PNG twoDtree::render()
{

	// YOUR CODE HERE!!
	PNG res(width, height);
	render_helper(res, root);
	return res;
}
int twoDtree::binary_search(int low,int high,int target){

		 while (low <= high)
				 {
					 int mid = (low + high) / 2;
				
					 if (target > pruneSize(mid)){
						 high = mid - 1;
					 }
					 else if (target < pruneSize(mid)){
						 low = mid + 1;
					 }
					 else{
						return mid;
					 }
	
				 }
		return -1;

}
int twoDtree::idealPrune(int leaves)
{
	if (pruneSize(0)==leaves){
		return 0;
	}
	int low = 1;
	int high = 300000;
	int target = leaves;
	int res = 300000;

	while(binary_search(low,high,target)!=-1){
		res = binary_search(low,high,target);
		high = res-1;
	}



	// 			 while (low <= high)
	// 			 {
	// 				 int mid = (low + high) / 2;
				
	// 				 if (target < pruneSize(mid)){
	// 					 high = mid - 1;
	// 				 }
	// 				 else if (target > pruneSize(mid)){
	// 					 low = mid + 1;
	// 				 }
	// 				 else{
	// 					prelim_result = mid;
	// 				 }
	
	// 			 }

	// int res = prelim_result;
	// while(prelim_result>0){
	// 	if (pruneSize(prelim_result-1)==target){
	// 		prelim_result--;
	// 		res = prelim_result;
	// 	}
	// 	else{
	// 		break;
	// 	}
	// }

	return res;

	
}

int twoDtree::pruneSize(int tol)
{
	int res = 0;
	pruneSize_helper(root,tol,res);
	return res;
	
}

void twoDtree::pruneSize_helper(twoDtree::Node* node, int tol, int& res){
	if (node==NULL){
		return;
	}
	
	if (leaves_within_tol(node->left,node->avg,tol) && leaves_within_tol(node->right,node->avg,tol)){
		res++;
	}
	else{
		pruneSize_helper(node->left,  tol, res);
		pruneSize_helper(node->right, tol, res);
	}

}



void twoDtree::prune(int tol)
{
	prune(tol, root);
}

twoDtree::Node *twoDtree::prune(int tol, twoDtree::Node *node)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->left == NULL && node->right == NULL)
	{
		return node;
	}
	if (leaves_within_tol(node, node->avg, tol))
	{
		node->left = NULL;
		node->right = NULL;
	}
	else
	{
		node->left = prune(tol, node->left);
		node->right = prune(tol, node->right);
	}
	return node;
}

bool twoDtree::leaves_within_tol(twoDtree::Node *node, RGBAPixel &root_avg, int tol)
{
	if (node == NULL || node == nullptr)
	{
		return true;
	}

	if (node->left == NULL && node->right == NULL)
	{
		long res1 = (root_avg.r - (node->avg.r)) * (root_avg.r - (node->avg.r));
		long res2 = (root_avg.g - (node->avg.g)) * (root_avg.g - (node->avg.g));
		long res3 = (root_avg.b - (node->avg.b)) * (root_avg.b - (node->avg.b));
		return res1 + res2 + res3<=tol;
	}

	return (leaves_within_tol(node->left, root_avg, tol) && leaves_within_tol(node->right, root_avg, tol));
}

void twoDtree::clear()
{

	// YOUR CODE HERE!!
}

void twoDtree::copy(const twoDtree &orig)
{
	height = orig.height;
	width = orig.width;
	root = copy_helper(orig.root);
}

twoDtree::Node *twoDtree::copy_helper(twoDtree::Node *node)
{
	if (node == NULL)
	{
		return NULL;
	}

	twoDtree::Node *res = new twoDtree::Node(node->upLeft, node->lowRight, node->avg);
	res->left = copy_helper(node->left);
	res->right = copy_helper(node->right);
	return res;
}

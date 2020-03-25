
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

	// YOUR CODE HERE!!
	// std::cout<<"new node created\n";
	twoDtree::Node* res = new twoDtree::Node(ul,lr,s.getAvg(ul, lr));

	res->left = NULL;
	res->right = NULL;

	if (ul == lr)
	{
		return res;
	}

	else if (vert)
	{
		if (lr.first - ul.first<1)
		{
			res->left = buildTree(s, ul, lr, false);
			res->right = buildTree(s, ul, lr, false);
		}
		else
		{
			int best_x_split = ul.first;
			double running_lowest_var = std::numeric_limits<double>::infinity();
			for (int x = ul.first; x <= lr.first - 1; x++)
			{

				long left_score = s.getScore(ul, pair<int, int>(x, lr.second));
				long right_score = s.getScore(pair<int, int>(x + 1, ul.second), lr);
				if (left_score + right_score <= running_lowest_var)
				{
					best_x_split = x;
					running_lowest_var = left_score + right_score;
				}
			}

			res->left = buildTree(s, ul, pair<int, int>(best_x_split, lr.second), false);
			res->right = buildTree(s, pair<int, int>(best_x_split + 1, ul.second), lr, false);
		}
	}

	else
	{

		if (lr.second - ul.second < 1)
		{
			res->left = buildTree(s, ul, lr, true);
			res->right = buildTree(s, ul, lr, true);
		}
		else
		{
			int best_y_split = ul.second;
			double running_lowest_var = std::numeric_limits<double>::infinity();
			for (int y = ul.second; y <= lr.second - 1; y++)
			{
				long top_score = s.getScore(ul, pair<int, int>(lr.first, y));
				long bot_score = s.getScore(pair<int, int>(ul.first, y + 1), lr);
				if (top_score + bot_score <= running_lowest_var)
				{
					best_y_split = y;
					running_lowest_var = top_score + bot_score;
				}
			}
			res->left = buildTree(s, ul, pair<int, int>(lr.first, best_y_split), true);
			res->right = buildTree(s, pair<int, int>(ul.first, best_y_split + 1), lr, true);
		}
	}

	return res;
}

void twoDtree::render_helper(PNG& img, twoDtree::Node* root){
if (root==NULL){
	return;
}

if (root->left==NULL && root->right == NULL){
	img.getPixel(root->upLeft.first,root->upLeft.second)->r = root->avg.r;
	img.getPixel(root->upLeft.first,root->upLeft.second)->g = root->avg.g;
	img.getPixel(root->upLeft.first,root->upLeft.second)->b = root->avg.b;
	img.getPixel(root->upLeft.first,root->upLeft.second)->a = root->avg.a;
}
render_helper(img,root->left);
render_helper(img,root->right);



}
PNG twoDtree::render()
{

	// YOUR CODE HERE!!
	PNG res(width,height);
	render_helper(res,root);
	return res;

}

int twoDtree::idealPrune(int leaves)
{

	// YOUR CODE HERE!!
}

int twoDtree::pruneSize(int tol)
{

	// YOUR CODE HERE!!
}

void twoDtree::prune(int tol)
{

	// YOUR CODE HERE!!
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

twoDtree::Node* twoDtree::copy_helper(twoDtree::Node* node){
	if (node==NULL){
		return NULL;
	}

	twoDtree::Node* res = new twoDtree::Node(node->upLeft,node->lowRight,node->avg);
	res->left = copy_helper(node->left);
	res->right = copy_helper(node->right);
	return res;


}

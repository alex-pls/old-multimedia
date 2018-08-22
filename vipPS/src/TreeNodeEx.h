
namespace vipPS
{
using namespace System::Windows::Forms;

public __gc class TreeNodeEx : public System::Windows::Forms::TreeNode
{
public:

	TreeNodeEx(void) : TreeNode()
	{
		project = NULL;
		file = NULL;
	}

	TreeNodeEx(String* text) : TreeNode(text)
	{
		project = NULL;
		file = NULL;
	}

	TreeNodeEx(vipPkgProject* prj) : TreeNode()
	{
		project = prj;
		file = NULL;
		Text = prj->FriendlyName;
	}

	TreeNodeEx(vipPKGFile* f) : TreeNode()
	{
		project = NULL;
		file = f;
		Text = f->ToString();
	}

	vipPkgProject* project;
	vipPKGFile* file;
};


}
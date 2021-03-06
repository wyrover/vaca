// Vaca - Visual Application Components Abstraction
// Copyright (c) 2005-2010 David Capello
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in
//   the documentation and/or other materials provided with the
//   distribution.
// * Neither the name of the author nor the names of its contributors
//   may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef VACA_TREENODE_H
#define VACA_TREENODE_H

#include "Vaca/base.h"
#include "Vaca/Component.h"
#include "Vaca/NonCopyable.h"

#include <vector>

namespace Vaca {

typedef std::vector<TreeNode*> TreeNodeList;

/**
   A TreeView node.  It has a text label, an image, a selected image
   asociated, and a state (collapsed/expanded). A node can be parent
   of sub-TreeNodes.
*/
class VACA_DLL TreeNode : public Component
{
  friend class TreeView;
  friend class TreeViewIterator;

  String       m_text;
  int          m_image;
  int          m_selectedImage;
  TreeNode*    m_parent;
  TreeNodeList m_children;
  HTREEITEM    m_handle;
  TreeView*    m_owner;
  bool         m_deleted;

public:

  TreeNode(const String& text = L"", int imageIndex = -1, int selectedImageIndex = -1);
  virtual ~TreeNode();

  TreeNode* getParent();
  TreeNodeList getChildren();
  TreeView* getTreeView();

  void addNode(TreeNode* node);
  void removeNode(TreeNode* node);

  bool isAncestorOf(TreeNode* child) const;

  virtual bool hasChildren();
  virtual String getText();
  virtual int getImage();
  virtual int getSelectedImage();

  void setText(const String& text);
  void setImage(int imageIndex);
  void setSelectedImage(int selectedImageIndex);

  bool isExpanded();
  void setExpanded(bool state);

  Rect getBounds() const;
  Rect getRowBounds() const;
  void ensureVisible();

  HTREEITEM getHandle();

  static TreeNode* fromHandle(HWND hwnd, HTREEITEM htreeitem);

protected:

  // New events
  virtual void onBeforeExpand(TreeViewEvent& ev);
  virtual void onBeforeCollapse(TreeViewEvent& ev);
  virtual void onBeforeSelect(TreeViewEvent& ev);
  virtual void onBeforeLabelEdit(TreeViewEvent& ev);
  virtual void onAfterExpand(TreeViewEvent& ev);
  virtual void onAfterCollapse(TreeViewEvent& ev);
  virtual void onAfterSelect(TreeViewEvent& ev);
  virtual void onAfterLabelEdit(TreeViewEvent& ev);

private:

  void addToTreeView(TreeView* treeView);
  void removeFromTreeView();

};

} // namespace Vaca

#endif // VACA_TREENODE_H

/******************************************************************************
Copyright (C) 2010-2013,2019,2020 Rodrigo Hernandez Cordoba

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
******************************************************************************/
#include <iostream>
#include <string>
#include "Node.h"
#include "aeongui/Color.h"

namespace AeonGUI
{
    Node::Node() = default;
    Node::~Node() = default;

    const std::vector<std::unique_ptr<Node>>& Node::childNodes() const
    {
        return mChildren;
    }

    bool Node::IsDrawEnabled() const
    {
        return true;
    }

    void Node::DrawStart ( Canvas& aCanvas ) const
    {
        // Do nothing by default
        ( void ) aCanvas;
    }

    void Node::DrawFinish ( Canvas& aCanvas ) const
    {
        // Do nothing by default
        ( void ) aCanvas;
    }

    void Node::Load ()
    {
    }

    void Node::Unload ()
    {
    }

    Node* Node::parentNode() const
    {
        return mParent;
    }
    Node* Node::parentElement() const
    {
        if ( mParent && mParent->nodeType() == ELEMENT_NODE )
        {
            return mParent;
        }
        return nullptr;
    }

    /*  This is ugly, but it is only way to use the same code for the const and the non const version
        without having to add template or friend members to the class declaration. */
#define TraverseDepthFirstPreOrder(...) \
    void Node::TraverseDepthFirstPreOrder ( const std::function<void ( __VA_ARGS__ Node* ) >& aAction ) __VA_ARGS__ \
    {\
        /** @todo (EC++ Item 3) This code is the same as the constant overload,\
        but can't easily be implemented in terms of that because of aAction's Node parameter\
        need to also be const.\
        */\
        auto node{this};\
        aAction ( node );\
        auto parent = mParent;\
        while ( node != parent )\
        {\
            if ( node->mIterator < node->mChildren.size() )\
            {\
                auto prev = node;\
                node = node->mChildren[node->mIterator].get();\
                aAction ( node );\
                prev->mIterator++;\
            }\
            else\
            {\
                node->mIterator = 0; /* Reset counter for next traversal.*/\
                node = node->mParent;\
            }\
        }\
    }

    TraverseDepthFirstPreOrder ( const )
    TraverseDepthFirstPreOrder( )
#undef TraverseDepthFirstPreOrder

#define TraverseDepthFirstPostOrder(...) \
    void Node::TraverseDepthFirstPostOrder ( const std::function<void ( __VA_ARGS__ Node* ) >& aAction ) __VA_ARGS__ \
    { \
        /* \
        This code implements a similar solution to this stackoverflow answer: \
        http://stackoverflow.com/questions/5987867/traversing-a-n-ary-tree-without-using-recurrsion/5988138#5988138 \
        */ \
        auto node{this}; \
        auto parent = mParent; \
        while ( node != parent ) \
        { \
            if ( node->mIterator < node->mChildren.size() ) \
            { \
                auto prev = node; \
                node = node->mChildren[node->mIterator].get(); \
                ++prev->mIterator; \
            } \
            else \
            { \
                aAction ( node ); \
                node->mIterator = 0; /* Reset counter for next traversal. */ \
                node = node->mParent; \
            } \
        } \
    }

    TraverseDepthFirstPostOrder ( const )
    TraverseDepthFirstPostOrder( )
#undef TraverseDepthFirstPostOrder


#define TraverseDepthFirstPostOrder(...) \
    void Node::TraverseDepthFirstPreOrder ( \
        const std::function<void ( __VA_ARGS__ Node* ) >& aPreamble, \
        const std::function<void ( __VA_ARGS__ Node* ) >& aPostamble ) __VA_ARGS__ \
    { \
        auto node = this; \
        aPreamble ( node ); \
        auto parent = mParent; \
        while ( node != parent ) \
        { \
            if ( node->mIterator < node->mChildren.size() ) \
            { \
                auto prev = node; \
                node = node->mChildren[node->mIterator].get(); \
                aPreamble ( node ); \
                ++prev->mIterator; \
            } \
            else \
            { \
                aPostamble ( node ); \
                node->mIterator = 0; \
                node = node->mParent; \
            } \
        } \
    }

    TraverseDepthFirstPostOrder ( const )
    TraverseDepthFirstPostOrder( )
#undef TraverseDepthFirstPostOrder

#define TraverseDepthFirstPostOrder(...) \
    void Node::TraverseDepthFirstPreOrder ( \
        const std::function<void ( __VA_ARGS__ Node* ) >& aPreamble, \
        const std::function<void ( __VA_ARGS__ Node* ) >& aPostamble, \
        const std::function<bool ( __VA_ARGS__ Node* ) >& aUnaryPredicate ) __VA_ARGS__ \
    { \
        if(!aUnaryPredicate(this)){return;} \
        auto node = this; \
        aPreamble ( node ); \
        auto parent = mParent; \
        while ( node != parent ) \
        { \
            if ( node->mIterator < node->mChildren.size() && aUnaryPredicate(node)) \
            { \
                auto prev = node; \
                node = node->mChildren[node->mIterator].get(); \
                aPreamble ( node ); \
                ++prev->mIterator; \
            } \
            else \
            { \
                aPostamble ( node ); \
                node->mIterator = 0; \
                node = node->mParent; \
            } \
        } \
    }

    TraverseDepthFirstPostOrder ( const )
    TraverseDepthFirstPostOrder( )
#undef TraverseDepthFirstPostOrder

    Node* Node::AddNode ( std::unique_ptr<Node> aNode )
    {
        aNode->mParent = this;
        return mChildren.emplace_back ( std::move ( aNode ) ).get();
    }

    std::unique_ptr<Node> Node::RemoveNode ( const Node* aNode )
    {
        std::unique_ptr<Node> result{};
        auto i = std::find_if ( mChildren.begin(), mChildren.end(), [aNode] ( const std::unique_ptr<Node>& Node )
        {
            return aNode == Node.get();
        } );
        if ( i != mChildren.end() )
        {
            result = std::move ( *i );
            mChildren.erase ( std::remove ( i, mChildren.end(), *i ), mChildren.end() );
        }
        result->mParent = nullptr;
        return result;
    }
}

#include "IScene.h"

void IScene::Draw()
{
	map<int, vector<shared_ptr<GameObject>>>::iterator renderLayer;

	for (renderLayer = mRenderLayers.begin(); renderLayer != mRenderLayers.end(); renderLayer++)
	{
		for (int i = 0; i < renderLayer->second.size(); i++)
		{
			renderLayer->second[i]->Draw();
		}
	}
}

#include "bulletmlrunner.h"
#include "bulletmlparser.h"
#include "bulletmlerror.h"
#include "formula-variables.h"
#include "bulletmlrunnerimpl.h"

BulletMLRunner::BulletMLRunner(BulletMLParser* bulletml) {
	const std::vector<BulletMLNode*>& acts = bulletml->getTopActions();
	for (size_t i = 0; i < acts.size(); i++) {
		std::vector<BulletMLNode*> act;
		act.push_back(acts[i]);
		BulletMLState* state =
        new BulletMLState(bulletml, act,
		bullet_shared_ptr<BulletMLParameter>());
		impl_.push_back(makeImpl(state));
	}
}

BulletMLRunner::BulletMLRunner(BulletMLState* state) {
	impl_.push_back(makeImpl(state));
}

BulletMLRunner::~BulletMLRunner() {
	for (size_t i = 0; i < impl_.size(); i++) {
		delete impl_[i];
	}
}

void BulletMLRunner::run() {
	for (std::vector<BulletMLRunnerImpl*>::const_iterator ite = impl_.begin();
		ite != impl_.end(); ++ite)
	{
			(*ite)->run();
	}
}

bool BulletMLRunner::isEnd() const {
	for (std::vector<BulletMLRunnerImpl*>::const_iterator ite = impl_.begin();
		ite != impl_.end(); ++ite)
	{
		if (!(*ite)->isEnd()) return false;
	}
	return true;
}

BulletMLRunnerImpl* BulletMLRunner::makeImpl(BulletMLState* state) {
	return new BulletMLRunnerImpl(state, this);
}

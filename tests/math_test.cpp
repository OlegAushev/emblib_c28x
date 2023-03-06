#include <c28x_emblib/tests/tests.h>
#include "float.h"


void emb::tests::math()
{
	EMB_ASSERT_EQUAL(emb::sgn(100), 1);
	EMB_ASSERT_EQUAL(emb::sgn(-100), -1);
	EMB_ASSERT_EQUAL(emb::sgn(3.14f), 1);
	EMB_ASSERT_EQUAL(emb::sgn(-3.14f), -1);
	EMB_ASSERT_EQUAL(emb::sgn(0), 0);
	EMB_ASSERT_EQUAL(emb::sgn(0.0f), 0);

	EMB_ASSERT_EQUAL(emb::sgn(-1.0f)*100.0f, -100.0f);
	EMB_ASSERT_EQUAL(emb::sgn(-1.0f)*(-100.0f), 100.0f);
	EMB_ASSERT_EQUAL(emb::sgn(1.0f)*(-100.0f), -100.0f);


	EMB_ASSERT_TRUE(emb::Range<float>(1, 10).contains(5));
	EMB_ASSERT_TRUE(!emb::Range<float>(1, 10).contains(0));
	EMB_ASSERT_TRUE(!emb::Range<float>(1, 10).contains(11));

	EMB_ASSERT_TRUE(emb::Range<float>(-10, -1).contains(-5));
	EMB_ASSERT_TRUE(!emb::Range<float>(-10, -1).contains(-11));
	EMB_ASSERT_TRUE(!emb::Range<float>(-10, -1).contains(0));

	EMB_ASSERT_TRUE(emb::Range<int>(5, 0).contains(2));
	EMB_ASSERT_TRUE(!emb::Range<int>(5, 0).contains(-1));
	EMB_ASSERT_TRUE(!emb::Range<int>(5, 0).contains(6));

	EMB_ASSERT_TRUE(emb::Range<int>(-5, 0).contains(-2));
	EMB_ASSERT_TRUE(!emb::Range<int>(-5, 0).contains(-6));
	EMB_ASSERT_TRUE(!emb::Range<int>(-5, 0).contains(1));

	EMB_ASSERT_TRUE(emb::Range<int>(0, 5).contains(0));
	EMB_ASSERT_TRUE(emb::Range<int>(0, 5).contains(5));


	emb::Integrator<float, float> integ(emb::Range<float>(-10.f, 10.f), 0.1f, -20.f);
	EMB_ASSERT_EQUAL(integ.result(), -10.f);
	for (size_t i = 0; i < 50; ++i)
	{
		integ.update(3);
	}
	EMB_ASSERT_TRUE(emb::Range<float>(4.999f, 5.001f).contains(integ.result()));
	integ.add(-10.f);
	EMB_ASSERT_TRUE(emb::Range<float>(-4.999f, -5.001f).contains(integ.result()));
	integ.reset();
	EMB_ASSERT_EQUAL(integ.result(), -10.f);
	for (size_t i = 0; i < 5000; ++i)
	{
		integ.update(1000);
	}
	EMB_ASSERT_EQUAL(integ.result(), 10.f);
	integ.add(-1000.f);
	EMB_ASSERT_EQUAL(integ.result(), -10.f);
	integ.update(FLT_MAX);
	EMB_ASSERT_EQUAL(integ.result(), 10.f);
	integ.update(-FLT_MAX);
	EMB_ASSERT_EQUAL(integ.result(), -10.f);
	integ.range.set_lo(-15.f);
	integ.update(-60);
	EMB_ASSERT_EQUAL(integ.result(), -15.f);
	EMB_ASSERT_EQUAL(integ.result(), integ.range.lo());
	integ.range.set_hi(20.f);
	integ.add(50.f);
	EMB_ASSERT_EQUAL(integ.result(), 20.f);
	EMB_ASSERT_EQUAL(integ.result(), integ.range.hi());
	integ.update(-6);
	EMB_ASSERT_TRUE(emb::Range<float>(19.399f, 19.401f).contains(integ.result()));
	integ.update(3);
	EMB_ASSERT_TRUE(emb::Range<float>(19.699f, 19.701f).contains(integ.result()));

	integ.range.set_hi(-20.f);
	EMB_ASSERT_EQUAL(integ.range.hi(), 20.f);
	integ.range.set_lo(21.f);
	EMB_ASSERT_EQUAL(integ.range.lo(), -15.f);
	integ.range.set_lo(20.f);
	EMB_ASSERT_EQUAL(integ.range.lo(), 20.f);
	integ.update(-3);
	EMB_ASSERT_EQUAL(integ.result(), 20.f);
}

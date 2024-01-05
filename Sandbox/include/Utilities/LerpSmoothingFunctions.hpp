#pragma once
# define PI           3.14159265358979323846

inline float EaseOutElastic(float t) {
	const float c4 = (PI * 1.1f) / 3.0f;

	return !t ? 0.0f : t == 1.0f ? 1.0f : std::powf(2.0f, -10.0f * t) * std::sinf((t * 10.0f - 0.75f) * c4) + 1.0f;
}

inline float EaseInElastic(float t) {
	const float c4 = (2.0f * PI) / 3.0f;

	return t == 0.0f ? 0.0f : t == 1.0f ? 1.0f : -std::powf(2.0f, 10.0f * t - 10.0f) * std::sinf((t * 10.0f - 10.75f) * c4);
}

inline float EaseOutQuart(float t) {
	return 1.0f - std::pow(1.0f - t, 4);
}

inline float EaseInOutExpo(float t) {
	return t == 0.0f ? 0 : t == 1.0f ? 1.0f : t < 0.5f ? std::pow(2.0f, 20.0f * t - 10.0f) / 2.0f : (2.0f - std::pow(2.0f, -20.0f * t + 10.0f)) / 2.0f;
}

inline float EaseInOutCubic(float t) {
	return t < 0.5 ? 4 * t * t * t : 1 - std::pow(-2 * t + 2, 3) / 2;
}

inline float EaseOutBack(float t) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return 1 + c3 * std::powf(t - 1.0f, 3.0f) + c1 * std::powf(t - 1.0f, 2.0f);
}

inline float EaseOutBounce(float t) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (t < 1.0f / d1)
		return n1 * t * t;

	else if (t < 2.0f / d1)
		return n1 * (t -= 1.5 / d1) * t + 0.75f;

	else if (t < 2.5f / d1)
		return n1 * (t -= 2.25f / d1) * t + 0.9375f;

	else
		return n1 * (t -= 2.625f / d1) * t + 0.984375f;
}

inline float EaseInCirc(float t) {
	return 1 - sqrt(1 - std::pow(t, 2));
}

inline float EaseInBounce(float t) {
	return 1.0f - EaseOutBounce(1.0f - t);
}

inline float EaseInQuint(float t) {
	return std::pow(t, 5);
}
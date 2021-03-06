#pragma once

#include "hash.hpp"
#include "reflection/Reflectible.hpp"

namespace putils {
    template<typename Precision, std::size_t Dimensions = 2>
    struct Point : putils::Reflectible<Point<Precision, Dimensions>> {
		union {
			Precision raw[2];
			struct {
				Precision x;
				Precision y;
			};
		};

        Point(Precision x = 0, Precision y = 0)
                : x(x), y(y) {}

        Point(const Point &) noexcept = default;
        Point & operator=(const Point &) noexcept = default;

        template<typename P>
        Point(const Point<P, 2> & other) noexcept : x((Precision)other.x), y((Precision)other.y) {}
        template<typename P>
		Point & operator=(const Point<P, 2> & other) noexcept {
			x = (Precision)other.x; y = (Precision)other.y;
			return *this;
		}

        template<typename P>
        Point(const Point<P, 3> & other) noexcept : x((Precision)other.x), y((Precision)other.y) {}
        template<typename P>
		Point & operator=(const Point<P, 3> & other) noexcept {
			x = (Precision)other.x; y = (Precision)other.y;
			return *this;
		}

        template<typename P>
        bool operator==(const Point<P> & rhs) const noexcept { return x == rhs.x && y == rhs.y; }

        template<typename P>
        bool operator!=(const Point<P> & rhs) const noexcept { return !(*this == rhs); }

        template<typename P>
        Point operator+(const Point<P> & rhs) const noexcept { return { x + rhs.x, y + rhs.y }; }

        template<typename P>
        Point & operator+=(const Point<P> & rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        template<typename P>
        Point operator-(const Point<P> & rhs) const noexcept { return { x - rhs.x, y - rhs.y }; }

        template<typename P>
        Point & operator-=(const Point<P> & rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

		Point operator*(const Point & rhs) const noexcept { return { x * rhs.x, y * rhs.y }; }
		Point & operator*=(const Point & rhs) const noexcept { x *= rhs.x; y *= rhs.y; return *this; }

		Point operator*(float rhs) const noexcept { return { x * rhs, y * rhs }; }
		Point & operator*=(float rhs) const noexcept { x *= rhs; y *= rhs; return *this; }

		Point operator/(const Point & rhs) const noexcept { return { x / rhs.x, y / rhs.y }; }
		Point & operator/=(const Point & rhs) const noexcept { x /= rhs.x; y /= rhs.y; return *this; }

		Point operator/(float rhs) const noexcept { return { x / rhs, y / rhs }; }
		Point & operator/=(float rhs) const noexcept { x /= rhs; y /= rhs; return *this; }

        float getDistanceTo(const Point & rhs) const noexcept {
            return std::sqrtf(
                    std::powf((float)x - (float)rhs.x, 2) +
                    std::powf((float)y - (float)rhs.y, 2)
            );
        }

		float getLengthSquared() const noexcept {
			return x * x + y * y;
		}

        float getLength() const noexcept {
            return std::sqrtf(getLengthSquared());
        }

        float getAngleTo(const Point & rhs) const noexcept {
            return std::atan2f((float)y - (float)rhs.y, (float)rhs.x - (float)x);
        }

		void normalize(float desiredLength = 1) {
			auto n = getLength();
			if (n > 0.0f) {
				n = desiredLength / n;
				x *= (Precision)n;
				y *= (Precision)n;
			}
		}

        pmeta_get_class_name("Point2");
        pmeta_get_attributes(
                pmeta_reflectible_attribute(&Point::x),
                pmeta_reflectible_attribute(&Point::y)
        );
        pmeta_get_methods(
                pmeta_reflectible_attribute(&Point::getDistanceTo),
                pmeta_reflectible_attribute(&Point::getLength),
                pmeta_reflectible_attribute(&Point::getAngleTo),
                pmeta_reflectible_attribute(&Point::normalize)
        );
        pmeta_get_parents();
    };

    template<typename Precision, std::size_t Dimensions = 2>
    struct Rect : public Reflectible<Rect<Precision, Dimensions>> {
        Point<Precision> position;
        Point<Precision> size;

        Rect(Point<Precision, Dimensions> position = {}, Point<Precision, Dimensions> size = {})
                : position(position), size(size) {}

        bool operator==(const Rect & rhs) const { return position == rhs.position && size == rhs.size; }

        bool operator!=(const Rect & rhs) const { return !(*this == rhs); }

        pmeta_get_class_name("Rect2");
        pmeta_get_attributes(
                pmeta_reflectible_attribute(&Rect::position),
                pmeta_reflectible_attribute(&Rect::size)
        );
    };

    template<typename Precision>
    struct Point<Precision, 3> : public Reflectible<Point<Precision, 3>> {
		union {
			Precision raw[3];
			struct {
				Precision x;
				Precision y;
				Precision z;
			};
		};

        Point(Precision x = 0, Precision y = 0, Precision z = 0)
                : x(x), y(y), z(z) {}

        Point(const Point &) noexcept = default;
        Point & operator=(const Point &) noexcept = default;

        template<typename P>
        Point(const Point<P, 2> & other) noexcept : x((Precision)other.x), y((Precision)other.y), z(0) {}
        template<typename P>
		Point & operator=(const Point<P, 2> & other) noexcept {
			x = (Precision)other.x; y = (Precision)other.y; z = 0;
			return * this;
		}

        template<typename P>
        Point(const Point<P, 3> & other) : x((Precision)other.x), y((Precision)other.y), z((Precision)other.z) {}
		template<typename P>
		Point & operator=(const Point<P, 3> & other) noexcept {
			x = (Precision)other.x; y = (Precision)other.y; z = (Precision)other.z;
			return * this;
		}

        bool operator==(const Point & rhs) const noexcept { return x == rhs.x && y == rhs.y && z == rhs.z; }

        bool operator!=(const Point & rhs) const noexcept { return !(*this == rhs); }

        Point operator-() const noexcept { return { -x, -y, -z }; }

        Point operator+(const Point & rhs) const noexcept { return { x + rhs.x, y + rhs.y, z + rhs.z }; }

        Point & operator+=(const Point & rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        Point operator-(const Point & rhs) const noexcept { return { x - rhs.x, y - rhs.y, z - rhs.z }; }

        Point & operator-=(const Point & rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

		Point operator*(const Point & rhs) const noexcept { return { x * rhs.x, y * rhs.y, z * rhs.z }; }
		Point & operator*=(const Point & rhs) noexcept { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }

		Point operator*(float rhs) const noexcept { return { x * rhs, y * rhs, z * rhs }; }
		Point & operator*=(float rhs) noexcept { x *= rhs; y *= rhs; z *= rhs; return *this; }

		Point operator/(const Point & rhs) const noexcept { return { x / rhs.x, y / rhs.y, z / rhs.z }; }
		Point & operator/=(const Point & rhs) noexcept { x /= rhs.x; y /= rhs.y; z /= rhs.z; return *this; }

		Point operator/(float rhs) const noexcept { return { x / rhs, y / rhs, z / rhs }; }
		Point & operator/=(float rhs) noexcept { x /= rhs; y /= rhs; z /= rhs; return *this; }

        float getDistanceTo(const Point & rhs) const noexcept {
            return std::sqrtf(
                    std::powf((float)x - (float)rhs.x, 2.f) +
                    std::powf((float)y - (float)rhs.y, 2.f) +
                    std::powf((float)z - (float)rhs.z, 2.f)
            );
        }

		float getLengthSquared() const noexcept {
			return x * x + y * y + z * z;
		}

        float getLength() const noexcept {
            return std::sqrtf(getLengthSquared());
        }

		float getAngleTo(const Point & rhs) const noexcept {
			const auto dot = x * rhs + y * rhs.y + z * rhs.z;
			return std::acos(dot / std::sqrtf(getLengthSquared() * rhs.getLengthSquared()));
		}

		float getYawTo(const Point & rhs) const noexcept {
			const auto dx = rhs.x - x;
			const auto dz = rhs.z - z;
			return -std::atan2f(dz, dx);
		}

		float getPitchTo(const Point & rhs) const noexcept {
			const auto dx = rhs.x - x;
			const auto dy = rhs.y - y;
			const auto dz = rhs.z - z;
			return -std::atan2f(std::sqrtf(dz * dz + dx * dx), dy) + 3.14159265359f / 2.f;
		}

		void normalize(float desiredLength = 1) {
			auto n = getLength();
			if (n > 0.0f) {
				n = desiredLength / n;
				x *= (Precision)n;
				y *= (Precision)n;
				z *= (Precision)n;
			}
		}

        pmeta_get_class_name("Point3");
        pmeta_get_attributes(
                pmeta_reflectible_attribute(&Point::x),
                pmeta_reflectible_attribute(&Point::y),
                pmeta_reflectible_attribute(&Point::z)
        );
        pmeta_get_methods(
                pmeta_reflectible_attribute(&Point::getDistanceTo),
                pmeta_reflectible_attribute(&Point::getLength),
                pmeta_reflectible_attribute(&Point::getYawTo),
                pmeta_reflectible_attribute(&Point::getPitchTo),
                pmeta_reflectible_attribute(&Point::normalize)
        );
    };

    template<typename Precision>
    struct Rect<Precision, 3> : public Reflectible<Rect<Precision, 3>> {
        Point<Precision, 3> position;
        Point<Precision, 3> size;

        Rect(Point<Precision, 3> position = {}, Point<Precision, 3> size = {})
                : position(position), size(size) {}

        bool operator==(const Rect & rhs) { return position == rhs.position && size == rhs.size; }

        bool operator!=(const Rect & rhs) { return !(*this == rhs); }

        pmeta_get_class_name("Rect3");
        pmeta_get_attributes(
                pmeta_reflectible_attribute(&Rect::position),
                pmeta_reflectible_attribute(&Rect::size)
        );
    };

	template<typename Precision, size_t Dimensions>
	using Vector = Point<Precision, Dimensions>;

    using Point3d = Point<double, 3>;
	using Vector3d = Point3d;
    using Rect3d = Rect<double, 3>;

    using Point2d = Point<double, 2>;
	using Vector2d = Point2d;
    using Rect2d = Rect<double, 2>;

    using Point3i = Point<int, 3>;
	using Vector3i = Point3i;
    using Rect3i = Rect<int, 3>;

    using Point2i = Point<int, 2>;
	using Vector2i = Point2i;
    using Rect2i = Rect<int, 2>;

    using Point3ui = Point<unsigned int, 3>;
	using Vector3ui = Point3ui;
    using Rect3ui = Rect<unsigned int, 3>;

    using Point2ui = Point<unsigned int, 2>;
	using Vector2ui = Point2ui;
    using Rect2ui = Rect<unsigned int, 2>;

    using Point3f = Point<float, 3>;
	using Vector3f = Point3f;
    using Rect3f = Rect<float, 3>;

    using Point2f = Point<float, 2>;
	using Vector2f = Point2f;
    using Rect2f = Rect<float, 2>;

	template<typename Precision>
	inline putils::Vector<Precision, 3> cross(const Vector<Precision, 3> & v, const Vector<Precision, 3> &v2) {
		return {
			v.y * v2.z - v.z * v2.y ,
			v.z * v2.x - v.x * v2.z ,
			v.x * v2.y - v.y * v2.x
		};
	}

	template<typename Precision>
	inline Precision dot(const Vector<Precision, 3> &v, const Vector<Precision, 3> &v2) {
		return v.x * v2.x + v.y * v2.y + v.z * v2.z;
	}
}

namespace std {
    template<typename Precision>
    struct hash<putils::Point<Precision>> {
        size_t operator()(const putils::Point<Precision> & coord) const noexcept {
            return putils::PairHash().operator()(std::make_pair(coord.x, coord.y));
        }
    };
}

namespace putils {
    template<typename Precision>
    using PointHash = std::hash<putils::Point<Precision>>;
}


class TestRectangle < MTest::Unit::TestCase
    def test_rect_init_with_zero_args
        rect = MRGSS::Rectangle.new
        assert(rect, "rect is created")
    end

    def test_rect_init_with_one_arg_should_fail
        rect = nil
        begin
            rect = MRGSS::Rectangle.new(1)
        rescue
            assert(rect.nil?, "rect cannot be created with one args")
        end
    end
    
    def test_rect_init_with_two_args_should_set_xy
        rect = MRGSS::Rectangle.new(5,10)
        assert_equal(rect.x, 5)
        assert_equal(rect.y, 10)
        assert(rect, "rect is created")
    end

    def test_rect_init_with_three_args_should_fail
        rect = nil
        begin
            rect = MRGSS::Rectangle.new(1,1,1)
        rescue
            assert(rect.nil?, "rect cannot be created with one args")
        end
    end

    def test_rect_init_with_four_args_should_create
        rect = MRGSS::Rectangle.new(5, 10, 15, 20)
        assert_equal(rect.x, 5)
        assert_equal(rect.y, 10)
        assert_equal(rect.width, 15)
        assert_equal(rect.height, 20)
        assert(rect, "rect is created")
    end

    def test_rect_accessors
        rect = MRGSS::Rectangle.new(5, 10, 15, 20)
        assert_equal(rect.x, 5)
        assert_equal(rect.y, 10)
        assert_equal(rect.width, 15)
        assert_equal(rect.height, 20)
        rect.x = 10
        rect.y = 15
        rect.width = 20
        rect.height = 25
        assert_equal(rect.x, 10)
        assert_equal(rect.y, 15)
        assert_equal(rect.width, 20)
        assert_equal(rect.height, 25)
    end

end  
MTest::Unit.new.run
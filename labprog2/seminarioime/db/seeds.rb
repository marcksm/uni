# coding: utf-8
# This file should contain all the record creation needed to seed the database with its default values.
# The data can then be loaded with the rails db:seed command (or created alongside the database with db:setup).
#
# Examples:
#
#   movies = Movie.create([{ name: 'Star Wars' }, { name: 'Lord of the Rings' }])
#   Character.create(name: 'Luke', movie: movies.first)

users = [{:name => "Rogerio",
          :email => "Rogerio@xol.com",
          :nusp => "987654",
          :usertype => false,
          :group_id  => 1,
          :password => "rogerio"},

         {:name => "Roberto",
          :email => "Roberto@xol.com",
          :nusp => "000000",
          :usertype => false,
          :group_id  => 1,
          :password => "password"},

          {:name => "Silvio",
           :email => "Silvio@usp.com",
           :nusp => "123456",
           :usertype => true,
           :group_id  => 2,
           :password => "silvio"},

         {:name => "Sergio",
           :email => "sergio@usp.com",
           :nusp => "111111",
           :usertype => true,
           :group_id  => 1,
           :password => "password"}
        ]

seminars = [{:name => "Learning & Avoiding Unforgivable Curses by Tom Marvolo Riddle",
             :description => "Tom Riddle will come to IME to teach how to pronounce 'Avada Kedavra' properly.",
             :place => "Auditório CCSL",
             :date => "2018-01-20 [12:35:00]"},

            {:name => "Learning to Fly by David Gilmour",
             :description => "Momentary Lapse of Reason",
             :place => "Auditório Jacy Monteiro",
             :date => "2018-02-01 [01:01:00]"},

            {:name => "How to Create an Seminar by Lucas",
             :description => "If you don't know, don't ask me.",
             :place => "Sala 5",
             :date => "2018-03-01 [01:01:00]"}]

# seminars.each do |seminar|
#   Seminar.create!(seminar)
# end

groups = [
	{ name: 'Sistemas de software' },
	{ name: 'Computação Musical' },
	{ name: 'Visão computacional'},
    { name: 'Outros'}]

groups.each do |group|
  Group.create!(group)
end

Group.find_by(name: 'Outros').seminars.create!(seminars)
Group.find_by(name: 'Outros').users.create!(users)

seminar1 = Seminar.find_by(name: "Learning & Avoiding Unforgivable Curses by Tom Marvolo Riddle")
User.find_by(name: "Sergio").responsibilities.create!(seminar_id: seminar1.id)

seminar2 = Seminar.find_by(name: "Learning to Fly by David Gilmour")
User.find_by(name: "Silvio").responsibilities.create!(seminar_id: seminar2.id)

seminar3 = Seminar.find_by(name: "How to Create an Seminar by Lucas")
User.find_by(name: "Sergio").responsibilities.create!(seminar_id: seminar3.id)

responsibility = Responsibility.find_by(seminar_id: seminar1.id)
User.find_by(name: "Rogerio").attendances.create!(responsibility_id: responsibility.id)





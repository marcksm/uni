class AddSeminarToInterest < ActiveRecord::Migration[5.1]
  def change
    add_reference :interests, :seminar, foreign_key: true
  end
end

class AddResponsibilityToAttendances < ActiveRecord::Migration[5.1]
  def change
    add_reference :attendances, :responsibility, foreign_key: true
  end
end

class CreateSeminars < ActiveRecord::Migration[5.1]
  def change
    create_table :seminars do |t|
      t.string :name
      t.text :description
      t.string :place
      t.datetime :date

      t.timestamps
    end
  end
end

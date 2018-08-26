class CreateResponsibilities < ActiveRecord::Migration[5.1]
  def change
    create_table :responsibilities do |t|

      t.timestamps
    end
  end
end
